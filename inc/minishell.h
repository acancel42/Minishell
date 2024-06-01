
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
<<<<<<< HEAD
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../inc/libft/libft.h"

=======
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include "lexer.h"
>>>>>>> main

typedef struct s_file
{
	char	*name;
	int		fd;
	bool	state;
}				t_file;

typedef struct s_commands
{
	char				*cmd;
	char				**paths;
	bool				valid_path;
	char				**flags;
	int					index;
	void				(*f)(void*);
	t_file				*input;
	t_file				*output;
	struct s_commands	*next;
}				t_commands;

char	*get_user(char **env);

#endif
