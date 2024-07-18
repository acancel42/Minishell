#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_types
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND_OUT,
	T_HEREDOC,
	T_D_QUOTED_WORD,
	T_S_QUOTED_WORD,
}	t_token_types;

typedef struct s_token
{
	char			*value;
	t_token_types	type;
	int				is_separated;
	struct s_token	*next;
}				t_token;

#endif
