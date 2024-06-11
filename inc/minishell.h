
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
	struct s_file	*next;
}				t_file;

typedef struct s_commands
{
	char				*name;
	char				*path;
	int					valid_path;
	void				(*f)(void*);
	t_file				*redirections;
	pid_t				pid;
	int					infile_fd;
	int					outfile_fd;
	char				**args;
	char				*user;
	struct s_commands	*next;
}			              t_commands;

char		**ft_get_env(char **env);
char		*get_user(char **env);
int			ft_exec_v1(t_commands *cmds, char **my_env);
int			get_pwd(char **pwd);
t_commands	*ft_cmdnew(char *user);
t_file		*ft_filenew(char *content, char *type);
t_token		*ft_toknew(char content, t_token_types type);
void		cmd_path(t_token *token, t_commands *cmds, char **env);
void		ft_cmdadd_back(t_commands **lst, t_commands *new);
void		ft_cmdsclear(t_commands **lst);
void		ft_fileadd_back(t_file **lst, t_file *new);
void		ft_fileclear(t_file **file);
void		ft_free_tab(char **arr);
void		ft_pathfinder(t_token *token, t_commands *cmds, char **env);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_tokenclear(t_token **token);
void		print_cmds(t_commands *cmds);
void		print_file(t_file *file);
void		print_lst(t_token *token);
void		print_type(t_token_types type);
void 		exit_minishell(t_token **token, t_commands **cmds, char **user);

#endif
