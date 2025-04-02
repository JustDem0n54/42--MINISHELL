/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:44:17 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 13:44:18 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_all_str_heredoc(t_var *var, char *str, int i, int y)
{
	char	*temp;
	char	*temp2;
	char	*newstr;
	int		prev_i;

	temp = NULL;
	temp2 = NULL;
	newstr = NULL;
	prev_i = 0;
	while ((size_t)i < ft_strlen(str))
	{
		y = prev_i;
		temp = check_dollars_heredoc(var, str, &i, y);
		if (temp2 != NULL)
			newstr = ft_strjoin(temp2, temp);
		if (temp2 != NULL)
			free(temp2);
		else
			newstr = ft_strdup(temp);
		temp2 = newstr;
		prev_i = i + 1;
		free(temp);
		i++;
	}
	return (newstr);
}

t_heredoc	init_hd(char *eof, int i)
{
	t_heredoc	hd;

	hd.i = 0;
	hd.n_eof = check_quote(eof, 0, 0);
	hd.file = ft_itoa(i);
	hd.fd = open(hd.file, O_WRONLY | O_TRUNC | O_CREAT | O_RDONLY, 00644);
	return (hd);
}

int	check_specificity(t_var *var, t_heredoc hd)
{
	if (hd.line == NULL)
	{
		ft_ctrl_d_heredoc(var, hd.n_eof);
		return (1);
	}
	hd.i++;
	if (hd.line && ((ft_strcmp(hd.line, hd.n_eof) == 0) || g_sig == SIGINT))
	{
		free (hd.line);
		if (g_sig == SIGINT)
		{
			close(hd.fd);
			hd.fd = open(hd.file, O_TRUNC | O_CREAT | O_RDONLY, 00644);
		}
		return (1);
	}
	return (0);
}

void	end_heredoc(t_var *var, t_heredoc hd)
{
	free(var->hd.n_eof);
	rl_event_hook = NULL;
	var->count_line += hd.i;
	close(var->hd.fd);
	var->hd.fd = open(var->hd.file, O_RDONLY);
	g_sig = 0;
	unlink(var->hd.file);
}

int	gest_heredoc(t_var *var, char *eof, int i)
{
	var->hd = init_hd(eof, i);
	g_sig = 1;
	rl_event_hook = ft_check_ctrl_c_heredoc;
	while (g_sig != SIGINT)
	{
		var->hd.line = readline(">");
		if (check_specificity(var, var->hd) == 1)
			break ;
		if (ft_strcmp(eof, var->hd.n_eof) == 0)
			var->hd.line = parse_all_str_heredoc(var, var->hd.line, 0, 0);
		if (var->hd.line != NULL)
			var->hd.line2 = ft_strjoin(var->hd.line, "\n");
		else
			var->hd.line2 = ft_strdup("\n");
		ft_putstr_fd(var->hd.line2, var->hd.fd);
		if (var->hd.line)
			free(var->hd.line);
		if (var->hd.line2)
			free(var->hd.line2);
	}
	end_heredoc(var, var->hd);
	return (free(var->hd.file), var->hd.fd);
}
