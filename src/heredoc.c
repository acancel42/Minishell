#include "minishell.h"

char	*generate_random_name(t_data *data, t_commands *cmds)
{
	int				fd;
	unsigned char	*name;
	char			*res;
	int				i;

	i = 0;
	name = ft_calloc((9), sizeof(unsigned char));
	if (!name)
		ft_exit(data->token, data->cmds, data);
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, name, 8);
	while (name[i] && name[i] != '\0')
	{
		name[i] = name[i] % 74 + 48;
		if (name[i] >= 58 && name[i] <= 63)
			name[i] = name[i] + 10;
		i++;
	}
	ft_close(fd, data, cmds, 2);
	res = ft_strjoin("/tmp/", (char *)name, 0);
	free(name);
	if (!res)
		return (NULL);
	return (res);
}

int	ft_write_heredoc(char *line, t_commands *cmds, char *name, char *delimiter)
{
	int	ret;

	ret = 0;
	line = readline(">");
	if (g_sigint == 2)
	{
		free (line);
		return (1);
	}
	if (cmds->infile_fd == -1)
		perror(name);
	if (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		write(cmds->infile_fd, line, ft_strlen(line));
		write(cmds->infile_fd, "\n", 1);
	}
	else
		ret = 1;
	free(line);
	return (ret);
}

int	handle_heredoc(t_data *data, t_commands *cmds, char *delimiter)
{
	char	*name;
	char	*line;
	int		ret;

	line = NULL;
	ft_close(cmds->infile_fd, data, cmds, 0);
	name = generate_random_name(data, cmds);
	if (!name)
		return (-1);
	cmds->infile_fd = open(name, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
	if (cmds->infile_fd == -1)
		perror(name);
	while (1)
	{
		ft_signalhandle();
		if (ft_write_heredoc(line, cmds, name, delimiter) == 1)
			break ;
	}
	ft_close(cmds->infile_fd, data, cmds, 2);
	cmds->infile_fd = open(name, O_RDONLY);
	if (cmds->infile_fd == -1)
		perror(name);
	unlink(name);
	free(name);
	ret = g_sigint;
	g_sigint = 0;
	return (ret);
}
