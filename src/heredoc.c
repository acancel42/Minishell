#include "minishell.h"

char	*generate_random_name(t_data *data)
{
	int				fd;
	unsigned char	*name;
	size_t			size;
	int				i;

	size = 8;
	i = 0;
	name = ft_calloc((size + 1), sizeof(unsigned char));
	if (!name)
		exit_minishell(&data->token, &data->cmds, data);
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, name, size);
	while (name[i] && name[i] != '\0')
	{
		name[i] = name[i] % 74 + 48;
		if (name[i] >= 58 && name[i] <= 63)
			name[i] = name[i] + 10;
		i++;
	}
	return ((char *)name);
}

int	ft_write_heredoc(char *line, t_commands *cmds, char *name, char *delimiter)
{
	line = readline(">");
	cmds->outfile_fd = open(name, O_CREAT, 420);
	if (cmds->outfile_fd == -1)
		perror(name);
	if (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		write(cmds->outfile_fd, line, ft_strlen(line));
		write(cmds->outfile_fd, "\n", 1);
	}
	else
		return (1);
	return (0);
}

int	handle_heredoc(t_data *data, t_commands *cmds, char *delimiter)
{
	char	*name;
	char	*line;

	line = NULL;
	delimiter = ft_strdup(delimiter + 1);
	if (!delimiter)
		exit_minishell(&data->token, &data->cmds, data);
	name = generate_random_name(data);
	name = ft_strjoin("/tmp/", name, 0);
	if (!name)
		return (-1);
	while (1)
	{
		if (ft_write_heredoc(line, cmds, name, delimiter) == 1)
			break ;
	}
	close(cmds->outfile_fd);
	cmds->outfile_fd = STDOUT_FILENO;
	cmds->infile_fd = open(name, O_RDONLY);
	if (cmds->infile_fd == -1)
		perror(name);
	unlink(name);
	free(name);
	return (0);
}
