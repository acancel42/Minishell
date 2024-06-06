
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../inc/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "lexer.h"

typedef struct s_file
{
	char			*name;
	int				fd;
	bool			state;
	int				squoted;
	int				dquoted;
	struct s_file	*next;
}				t_file;

typedef struct s_commands
{
	char				*name;
	char				*path;
	int					valid_path;
	char				*flags;
	void				(*f)(void*);
	t_file				*redirections;
	t_file				*args;
	struct s_commands	*next;
}				t_commands;

char		*get_user(char **env);
void		cmd_path(t_commands *cmds, char **env);
void		free_all(t_commands **cmds, void *data);
void		print_type(t_token_types type);
void		print_lst(t_token *token);
void		print_file(t_file *file, t_token_types type);
void		print_cmds(t_commands *cmds);
void		ft_pathfinder(t_commands *cmds, char **env);
t_commands	*ft_cmdnew(void);
void		ft_cmdadd_back(t_commands **lst, t_commands *new);
void		ft_cmdsclear(t_commands **lst);
t_file		*ft_filenew(char *content, char *type);
void		ft_fileadd_back(t_file **lst, t_file *new);
void		ft_fileclear(t_file **file);
t_token		*ft_toknew(char content, t_token_types type);
void		ft_tokadd_back(t_token **lst, t_token *new);
int			get_pwd(char **pwd);
void		ft_free_tab(char **arr);
void		ft_tokenclear(t_token **token);


#endif