#include "../../minishell.h"

void	ft_ctrl_c(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
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
	}
	return;
}

void	ft_ctrl_slash(int sig)
{
	g_sig = sig;
	if (waitpid(-1, NULL, WNOHANG) == -1)
		return;
	else
		ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	ft_void(int sig)
{
	(void) sig;
	return;
}

void	manage_signal()
{
	if (SIGQUIT)
		signal(SIGQUIT, ft_ctrl_slash);
	if (SIGINT)
		signal(SIGINT, ft_ctrl_c);
	if (SIGPIPE)
		signal(SIGPIPE, ft_ctrl_c);
	}
// }


// int	ft_ctrl_d_heredoc(int sig)
// {
// 	if (line == NULL)
// 	{
// 		ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2)
// 		ft_putstr_fd(delimiter);
// 		ft_putstr_fd("')", 2);
// 	}
// }