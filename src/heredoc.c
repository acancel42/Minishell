#include "minishell.h"

void	grn_loop(unsigned char *c)
{
	*c = *c % 74 + 48;
	if (*c >= 58 && *c <= 63)
		*c = *c + 10;
}

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
	if (fd == -1)
		perror("/dev/urandom");
	if (read(fd, name, 8) == 1)
		perror("read");
	while (name[i] && name[i] != '\0')
	{
		grn_loop(&name[i]);
		i++;
	}
	ft_close(fd, data, cmds, 2);
	res = ft_strjoin("/tmp/", (char *)name, 0);
	free(name);
	if (!res)
		ft_exit(data->token, cmds, data);
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

int	handle_heredoc_return(t_data *data)
{
	int	ret;

	ret = g_sigint;
	g_sigint = 0;
	if (ret == 2)
		data->last_error_status = 130;
	return (ret);
}

int	handle_heredoc(t_data *data, t_commands *cmds, char *delimiter)
{
	char	*name;
	char	*line;

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
	return (handle_heredoc_return(data));
}
