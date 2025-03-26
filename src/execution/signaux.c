#include "../../minishell.h"

// void	(*signal (int sig, void(*ft_signal)(int)))(int);

void	ft_ctrl_c_parent(int sig)
{
	g_sig = sig;
	// if (waitpid(-1))
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return;		
}

void	ft_ctrl_c_child(int sig)
{
	g_sig = sig;
	ft_putstr_fd("test\n", 1);
	// if (sig == SIGINT)
	// 	rl_replace_line("", 0);
}

void	ft_ctrl_slash(int sig)
{
	// signal(SIGQUIT, SIG_DFL);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	g_sig = sig;

}

void	manage_signal(int opt)
{
	if (opt == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_ctrl_c_parent);
	}
	else if (opt == CHILD)
	{
		// ft_putstr_fd("dans child", 1);
		signal(SIGQUIT, ft_ctrl_slash);
		signal(SIGINT, ft_ctrl_c_child);
	}
}


// int	ft_ctrl_d_heredoc(int sig)
// {
// 	if (line == NULL)
// 	{
// 		ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2)
// 		ft_putstr_fd(delimiter);
// 		ft_putstr_fd("')", 2);
// 	}
// }