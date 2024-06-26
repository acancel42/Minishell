
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
# define RED "\033[1;91m\033[1m"
# define BLUE "\033[1;96m\033[1m"
# define RESET "\033[0m"

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
	int					fd_p[2];
	struct s_commands	*next;
}			              t_commands;

char		**ft_get_env(char **env);
char		*get_user(char **env);
int			ft_exec_v1(t_commands *cmds, char **my_env);
int			get_pwd(char **pwd);
t_commands	*ft_cmdnew(char *user);
t_file		*ft_filenew(char *content, char *type);
t_token		*ft_toknew(char content, t_token_types type);
int			token_init(char *src, t_token **token);
int			handle_output(char *src, t_token **token, int i);
int			handle_input(char *src, t_token **token, int i);
int			handle_pipe(t_token **token, int i);
int			handle_else(char *src, t_token **token, int i);
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
void		fill_cmd(t_commands **cmds, t_token *token, char **env);
void		init_cmd(t_commands **cmds, t_token *token, char *user);
void		lexer_init(t_token **token, char *src);
int			ft_cd(char *path,char **my_env);
char		*get_color(char *user, char *color);
char		*get_home(char **env);
int			ft_echo(char **args);
int			ft_wich_redir(t_commands *cmds);
void 		print_my_env(char **my_env);
int			ft_pipe(t_commands *cmds, char **my_env);

#endif
