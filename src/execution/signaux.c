#include "../../minishell.h"

void	ft_ctrl_c(int sig)
{
	if (g_sig == 1 && sig == SIGINT)
	{
		ft_putstr_fd("^C", 1);
		rl_done = 1;
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
	}
	g_sig = SIGINT;
	return ;
}

void	ft_ctrl_slash(int sig)
{
	(void) sig;
	if (waitpid(-1, NULL, WNOHANG) == -1)
		return ;
	else
		ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	ft_void(int sig)
{
	(void) sig;
	return ;
}

void	manage_signal(void)
{
	if (SIGQUIT)
		signal(SIGQUIT, ft_ctrl_slash);
	if (SIGINT)
		signal(SIGINT, ft_ctrl_c);
	if (SIGPIPE)
		signal(SIGPIPE, ft_ctrl_c);
}
