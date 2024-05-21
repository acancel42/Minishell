#ifndef		MINISHELL_H
# define	MINISHELL_H
# include <stdbool.h>

typedef struct s_file
{
	char	*name;
	int		fd;
	bool	state;
}				t_file;

typedef struct s_commands
{
	char				*name;
	char 				**paths;
	char				**flags;
	int					index;
	void				(*f)(void*);
	t_file				input;
	t_file				output;
	struct s_commands	*next;
}				t_commands;

#endif
