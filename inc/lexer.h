#ifndef	LEXER_H
# define	LEXER_H

typedef enum	e_token_types{
	INT,
	SCO,
	FLAG,
	CHAR,
	LPAR,
	RPAR,
	EQUAL,
	OP,
	IRED,
	ORED,
	SEMI,
}	t_token_types;

typedef struct	s_token
{
	char			*value;
	t_token_types	type;
	struct s_token	*next;
}				t_token;


#endif
