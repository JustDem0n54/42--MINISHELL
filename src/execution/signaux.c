#include "../../minishell.h"

// void	(*signal (int sig, void(*ft_signal)(int)))(int);

void	ft_ctrl_c(int sig)
{
	// g_ctrl = sig;
	// signal(SIGINT, SIG_DFL);
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return;		
}

// void	ft_ctrl_slash_parent(int sig)
// {
// 	// if (sig == SIGQUIT && g_ctrl != 0)
// 	// {
// 	// 	printf("Quit (core dumped)\n");
// 	// 	// printf("\n");
// 	// 	rl_replace_line("", 0);
// 	// 	rl_on_new_line();
// 	// 	return;
// 	// }
// 	// else
// 	// {
// 	g_ctrl = sig;
// 	signal(SIGQUIT, SIG_IGN);
// 	return;
// 	// }
// }

// void disable_ctrl_signals()
// {
//     struct termios term;

//     // Obtenir les paramètres actuels du terminal
//     tcgetattr(STDIN_FILENO, &term);  // STDIN_FILENO correspond à l'entrée standard (le terminal)

//     // Désactiver les signaux générés00 par le terminal (Ctrl+C, Ctrl+\)
//     term.c_lflag &= ~ISIG;  // Désactive ISIG, qui active le traitement des signaux comme Ctrl+C, Ctrl+\

//     // Appliquer les modifications
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);  // Applique les changements immédiatement
// }

void	ft_ctrl_slash_child(int sig)
{
	printf("ok");
	signal(SIGQUIT, SIG_DFL);
	printf("Quit (core dumped)\n");
	
	g_ctrl = sig;
	
	// signal(SIGQUIT, SIG_DFL);
	// printf("Quit (core dumped)\n");
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