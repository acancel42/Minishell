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
# include <sys/types.h>
# include <sys/wait.h>
# include "lexer.h"
# define RED "\033[1;91m\033[1m"
# define BLUE "\033[1;96m\033[1m"
# define RESET "\033[0m"

typedef struct s_commands
{
	char				*name;
	char				*path;
	int					valid_path;
	void				(*f)(void*);
	char				**redirections;
	pid_t				pid;
	int					index;
	int					infile_fd;
	int					outfile_fd;
	char				**args;
	char				*user;
	struct s_commands	*next;
}				t_commands;

typedef struct s_data
{
	t_commands	*cmds;
	t_token		*token;
	char		**my_env;
	char		**export;
	char		*line;
	char		*user;
	char		*home;
	int			pflag;
	int			rflag;
	int			index_max;
	int			last_error_status;
	pid_t		pid;
}				t_data;

void		ft_get_env(t_data *data, char **env);
char		**tab_join(char **tab, char *str);
char		*find_env_var(char *name, char **env);
char		*get_color(char *user, char *color);
char		*get_home(char **env);
char		*get_user(t_data *data);
int			cmd_path(t_data *data);
int			count_type_until_pipe(t_token *token, t_token_types type, int flag);
int			ft_cd(char *path, t_data *data);
int			ft_echo(t_commands *cmds);
int			ft_export(char **args, t_data *data);
int			ft_exec_built_in(t_data *data, t_commands *cmds);
int			ft_isword(t_token *token);
int			ft_pathfinder(t_data *data);
int			ft_pipe(t_commands *cmds, t_data *data, t_token *token);
int			ft_wich_redir(t_commands *cmds, int i);
int			get_pwd(char **pwd);
int			handle_else(char *src, t_token **token, t_data *data);
int			handle_input(char *src, t_token **token, t_data *data);
int			handle_output(char *src, t_token **token, t_data *data);
int			handle_pipe(t_token **token, t_data *data);
int			iredir_handle(char *line, int *i);
int			is_mult_op(char *line, int *i, int *multiple_op, int *is_word);
int			is_redir_or_pipe(t_data *data, int i);
int			oredir_handle(char *line, int *i);
int			pipe_handle(char *line, int *i);
int			prelexer_check(t_data *data);
int			token_init(char *src, int i, t_token **token, t_data *data);
t_commands	*ft_cmdnew(char *user, int flag);
t_token		*ft_toknew(char content, t_token_types type);
void		exec_cmd(t_data *data, t_commands *cmds);
void		exit_minishell(t_token **token, t_commands **cmds, t_data *data);
void		fill_cmd(t_commands **cmds, t_token *token, t_data *data);
void		free_data(t_data *data);
void		ft_cmdadd_back(t_commands **lst, t_commands *new);
void		ft_cmdsclear(t_commands **lst);
void		ft_exec_error(t_token *token, t_commands *cmds, \
							t_data *data, int flag);
void		ft_free_tab(char **arr);
void		ft_redir_or_append(t_commands *cmds);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_tokenclear(t_token **token);
void		init_cmd(t_commands **cmds, t_token *token, t_data *data);
void		init_cmd(t_commands **cmds, t_token *token, t_data *data);
void		lexer_init(t_token **token, t_data *data);
void		print_cmds(t_commands *cmds);
void		print_lst(t_token *token);
void		print_my_env(char **my_env);
void		print_type(t_token_types type);
int			ft_is_built_in(t_commands *cmds);
int			ft_pwd(void);
int			ft_env(t_data *data);

#endif
