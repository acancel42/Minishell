/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:15:19 by acancel           #+#    #+#             */
/*   Updated: 2024/05/21 19:18:51 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_read_and_join(char *buf, char *line, int fd);
char	*ft_clear_buf(char	*buf);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "\0";
	char		*line;

	if (fd < 0)
	{
		buf[0] = '\0';
		return (NULL);
	}
	line = ft_strjoin_gnl(NULL, buf);
	if (line == NULL)
		return (NULL);
	line = ft_read_and_join(buf, line, fd);
	if (line == NULL)
		return (NULL);
	*buf = *ft_clear_buf(buf);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_read_and_join(char *buf, char *line, int fd)
{
	ssize_t	size_read;
	char	*line_tmp;

	size_read = 1;
	while (size_read > 0 && !ft_is_strchr(buf, '\n'))
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			buf[0] = '\0';
			free(line);
			line = NULL;
			break ;
		}
		buf[size_read] = '\0';
		line_tmp = ft_strjoin_gnl(line, buf);
		if (line_tmp == NULL)
		{
			free(line);
			line = NULL;
			break ;
		}
		line = line_tmp;
	}
	return (line);
}

char	*ft_clear_buf(char	*buf)
{
	size_t		len_nl;
	size_t		i;

	len_nl = ft_strlen_or_len_to_nl(buf);
	i = 0;
	while (len_nl + i < BUFFER_SIZE + 1)
	{
		buf[i] = buf[len_nl + i];
		i++;
	}
	return (buf);
}
