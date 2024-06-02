
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../inc/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
// # include <ctype.h>
# include <string.h>
# include "lexer.h"

typedef struct s_file
{
	char	*name;
	int		fd;
	bool	state;
}				t_file;

typedef struct s_commands
{
	char				*name;
	char				*path;
	int				valid_path;
	char				**flags;
	void				(*f)(void*);
	t_file				*input;
	t_file				*output;
	struct s_commands	*next;
}				t_commands;

char	*get_user(char **env);
void	cmd_path(t_commands *cmds, char **env);


#endif
