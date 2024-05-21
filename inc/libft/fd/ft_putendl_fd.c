/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:54:24 by acancel           #+#    #+#             */
/*   Updated: 2024/01/27 16:25:44 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	check_write;

	if (!s)
		return (10);
	check_write = write(fd, s, ft_strlen(s));
	if (check_write == -1)
		return (-1);
	check_write = write(fd, "\n", 1);
	if (check_write == -1)
		return (-1);
	return (0);
}
