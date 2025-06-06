/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:43:32 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 13:43:33 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_error_path_cmd(t_var *var, t_exec *exec, char **env)
{
	int	status;

	status = 0;
	if (exec->cmd[0] && access(exec->cmd[0], F_OK) == 0)
		var->status = 126;
	else
		var->status = 127;
	if (exec->path == NULL)
	{
		if (exec->cmd[0] != NULL)
		{
			ft_putstr_fd(exec->cmd[0], 2);
			if (ft_strcmp(exec->cmd[0], "") == 0)
				ft_putstr_fd("'' ", 2);
		}
		ft_putstr_fd(": command not found\n", 2);
	}
	status = var->status;
	free_split(env);
	ft_free_all(var);
	exit(status);
}

void	(*ft_cmd(char **cmd))(t_var *var, char **tab)
{
	if (cmd[0] == NULL)
		return (NULL);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset);
	return (NULL);
}

void	setup_dup2(t_exec *exec)
{
	if (exec->input > 0)
	{
		dup2(exec->input, STDIN_FILENO);
		close(exec->input);
	}
	if (exec->output > 1)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
}

void	exec_one(t_var *var, t_exec *exec)
{
	pid_t	pid;
	char	**env;

	env = convert_env(var->env);
	pid = fork();
	if (pid == 0)
	{
		if (exec->input == -2 || exec->output == -2)
			return (ft_free_all(var), free_split(env), exit(1));
		if (exec->path == NULL || ft_strcmp(exec->path, "not found") == 0)
			return (setup_dup2(exec), ft_error_path_cmd(var, exec, env));
		setup_dup2(exec);
		if (execve(exec->path, exec->cmd, env) == -1)
		{
			return (free_split(env), perror(exec->cmd[0]),
				ft_free_all(var), exit (1));
		}
	}
	waitpid(pid, &var->status, 0);
	if (exec->input != -1)
		close(exec->input);
	var->status = var->status % 255;
	free_split(env);
	return ;
}

void	execution(t_var *var, t_exec *exec)
{
	void	(*builtins)(t_var *, char **);

	var->save_fd = 0;
	if (var->nbcmd == 1)
	{
		builtins = ft_cmd(exec->cmd);
		if (builtins == NULL)
			exec_one(var, exec);
		else
		{
			if (exec->input > 0)
				close(exec->input);
			if (exec->output == -1)
				exec->output = 1;
			exec->input = 0;
			var->save_fd = dup(1);
			setup_dup2(exec);
			builtins(var, exec->cmd);
			dup2(var->save_fd, 1);
			close(var->save_fd);
		}
		return ;
	}
	setup_exec(var, exec);
}
