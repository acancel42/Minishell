#include "minishell.h"

int	g_sigint = 0;

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_sigint = 1;
	}
	return ;
}

int	do_nothing(void)
{
	return (42);
}

int	main(int argc, char **argv, char **env)
{
	t_token				*token;
	t_commands			*cmds;
	t_data				*data;

	(void)argv;
	if (argc != 1)
		return (-1);
	data = ft_init_shell(env);
	token = NULL;
	cmds = NULL;
	while (1)
		ft_routine(token, cmds, data);
	return (0);
}
