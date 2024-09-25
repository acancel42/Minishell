/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:55:49 by acancel           #+#    #+#             */
/*   Updated: 2024/09/25 22:37:28 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include "lexer.h"
# define RED "\001\033[1;91m\033[1m\002"
# define BLUE "\001\033[1;96m\033[1m\002"
# define RESET "\001\033[0m\002"

typedef struct s_commands
{
	char				**args;
	char				**redirections;
	char				*name;
	char				*path;
	char				*user;
	int					index;
	int					infile_fd;
	int					outfile_fd;
	int					valid_path;
	pid_t				pid;
	struct s_commands	*next;
}						t_commands;

typedef struct s_expand
{
	int		s;
	int		e;
	int		i;
	bool	is_itoa;
}			t_expand;

typedef struct s_data
{
	bool		is_home;
	char		**export;
	char		**my_env;
	char		*home;
	char		*line;
	char		*user;
	int			index_max;
	int			last_error_status;
	int			pflag;
	int			rflag;
	t_expand	exp;
	pid_t		pid;
	t_commands	*cmds;
	t_token		*token;
}				t_data;

extern int	g_sigint;

char		**tab_dup(char **env);
char		**tab_join(char **tab, char *str);
char		**tab_replace(char **env, char *args);
char		*find_env_var(char *name, char **env);
char		*ft_strjoin_name(char *s1, char *s2, char c1, char c2);
char		*generate_random_name(t_data *data, t_commands *cmds);
char		*get_user(t_data *data);
int			cmd_not_found(t_commands *cmds, t_data *data);
int			cmd_path(t_data *data);
int			count_type_until_pipe(t_token *token, t_token_types type, int flag);
int			do_nothing(void);
int			expand_variables(char **dest, char *src, t_data *data);
int			fill_cmd(t_commands **cmds, t_token *token, t_data *data);
int			ft_append(t_data *data, t_commands *cmds, char *file, int flag);
int			ft_assign_value(char **name, char **value, \
							char **dest, t_data *data);
int			ft_cd(char *path, t_data *data, t_commands *cmds);
int			ft_data_init(t_data *data);
int			ft_echo(t_commands *cmds);
int			ft_env(t_data *data);
int			ft_envcmp(char *env, char *variable);
int			ft_exec_built_in(t_token *token, t_commands *cmds, t_data *data);
int			ft_export(char **args, t_data *data);
int			ft_is_built_in(t_commands *cmds);
int			ft_is_variable(char *str);
int			ft_isexport(char *args, char **env);
int			ft_isword(t_token *token);
int			ft_pathfinder(t_data *data);
int			ft_pipe(t_commands *temp, t_commands *cmds, \
						t_data *data, t_token *token);
int			ft_print_export(char **args, t_data *data);
int			ft_pwd(t_data *data);
int			ft_redir_or_append(t_data *data, t_commands *cmds);
int			ft_unset(char **args, t_data *data);
int			ft_wich_redir(t_data *data, t_commands *cmds, int i);
int			ft_wrong_path(t_data *data, int *exit_ret);
int			get_home(t_data *data);
int			get_pwd(char **pwd);
int			handle_double_quote(char *src, t_token **token, t_data *data);
int			handle_else(char *src, t_token **token, t_data *data);
int			handle_else(char *src, t_token **token, t_data *data);
int			handle_heredoc(t_data *data, t_commands *cmds, char *delimiter);
int			handle_input(char *src, t_token **token, t_data *data);
int			handle_output(char *src, t_token **token, t_data *data);
int			handle_pipe(t_token **token, t_data *data);
int			handle_pipe(t_token **token, t_data *data);
int			handle_single_quote(char *src, t_token **token, t_data *data);
int			iredir_handle(char *line, int *i);
int			is_mult_op(char *line, int *i, int *multiple_op, int *is_word);
int			is_redir_or_pipe(t_data *data, int i);
int			lexer_init(t_token **token, t_data *data);
int			oredir_handle(char *line, int *i);
int			pipe_handle(char *line, int *i);
int			prelexer_check(t_data *data);
int			skip_quoted(char quote, char *line, int i);
int			token_init(char *src, int i, t_token **token, t_data *data);
t_commands	*ft_cmdnew(int flag);
t_data		*ft_init_shell(char **env);
t_token		*ft_toknew(char content, t_token_types type);
void		build_path(t_data *data, char *s1, char *s2);
void		close_files(t_commands *cmds, t_data *data);
void		exec_cmds(t_data *data, t_commands *cmds);
void		exit_minishell(t_token **token, t_commands **cmds, t_data *data);
void		free_child(t_data *data, t_commands **cmds);
void		free_data(t_data *data, t_commands **cmds, t_token **token);
void		free_monitoring(char *host, char *username, char *pwd);
void		ft_close(int fd, t_data *data, t_commands *cmds, int flag);
void		ft_cmdadd_back(t_commands **lst, t_commands *new);
void		ft_cmdsclear(t_commands **lst);
void		ft_dup2(t_data *data, t_commands *cmds);
void		ft_exec_error(t_token *token, t_commands *cmds, \
							t_data *data, int flag);
void		ft_exit_monitoring(char *host, char *user, char *pwd, t_data *data);
void		ft_exit(t_token *token, t_commands *cmds, t_data *data);
void		ft_free_tab(char **arr);
void		ft_get_env(t_data *data, char **env);
void		ft_is_env_op(t_data *data);
void		ft_pwd_missing(t_data *data);
void		ft_replace_export(char ***nenv, char ***nexp, int i, t_data *data);
void		ft_routine( t_token *token, t_commands *cmds, t_data *data);
void		ft_signalhandle_in_child(void);
void		ft_signalhandle(void);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_tokenclear(t_token **token);
void		ft_variable_missing(t_data *data, char *variable, int flag);
void		ft_wait_signal(void);
void		get_color(t_data *data, char *color);
void		handle_rword_loop(t_token **token, t_data *data, char **temp);
void		handle_word(t_commands **cmds, t_token **token, \
						t_data *data, int *i);
void		init_cmd(t_commands **cmds, t_token *token, t_data *data);
void		init_cmd(t_commands **cmds, t_token *token, t_data *data);
void		print_cmds(t_commands *cmds);
void		print_lst(t_token *token);
void		print_my_env(char **my_env);
void		print_type(t_token_types type);
void		try_acces(t_data *data, char **all_paths, int i);

#endif
