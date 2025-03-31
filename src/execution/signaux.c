#include "../../minishell.h"

void	ft_ctrl_c(int sig)
{
	if (g_sig == 1 && sig == SIGINT)
	{
		ft_putstr_fd("^C", 1);
		rl_done = 1;
		g_sig = SIGINT;
	}
	else if (sig == SIGINT && g_sig != 1)
	{
		if (waitpid(-1, NULL, WNOHANG) == -1)
		{
			ft_putstr_fd("^C\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", 1);
		g_sig = SIGINT;
	}
}

void	ft_ctrl_slash(int sig)
{
	(void) sig;
	if (waitpid(-1, NULL, WNOHANG) == -1)
		return ;
	else
		ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	manage_signal(void)
{
	signal(SIGPIPE, ft_ctrl_c);
	if (SIGINT)
		signal(SIGINT, ft_ctrl_c);
	if (SIGQUIT)
		signal(SIGQUIT, ft_ctrl_slash);
}

int	ft_check_ctrl_c_heredoc(void)
{
	if (g_sig != SIGINT)
		return (1);
	return (0);
}

void	ft_ctrl_d_heredoc(t_var *var, char *eof)
{
	char	*nb_line;

	nb_line = ft_itoa(var->count_line);
	ft_putstr_fd("warning: here-document delimited at line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 1);
	ft_putstr_fd("')\n", 2);
	free (nb_line);
}
