typedef struct s_commands
{
	char				*name;
	char 				**paths;
	char				**flags;
	int					index;
	void				(*f)(void*);
	t_file				file;
	struct s_commands	*next;
}				t_commands;

typedef struct s_file
{
	t_file	input;
	t_file	output;
	char	*name;
	int		fd;
	bool	state;
}				t_file;

