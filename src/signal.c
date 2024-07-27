#include "minishell.h"

void ft_siginthandle(int sig)
{
	g_sigint = sig;
	rl_done = 1;
}

void ft_signalhandle(void)
{
	struct sigaction s_sa;

	sigemptyset(&s_sa.sa_mask);
	s_sa.sa_handler = &ft_siginthandle;
	s_sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_sa, NULL);
	s_sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_sa, NULL);
}

void	no_handler(int sig)
{
	(void)sig;
	return ;
}

void ft_wait_signal(void)
{
	struct sigaction s_sa;

	sigemptyset(&s_sa.sa_mask);
	s_sa.sa_handler = &no_handler;
	s_sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_sa, NULL);
}

void ft_signalhandle_in_child(void)
{
	struct sigaction s_sa;

	sigemptyset(&s_sa.sa_mask);
	s_sa.sa_handler = SIG_DFL;
	s_sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_sa, NULL);
}
