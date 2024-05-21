/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:07:57 by acancel           #+#    #+#             */
/*   Updated: 2024/01/12 13:53:17 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cset(char s1, char const *set);
int	ft_param(va_list args, const char format, int pl);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		pl;
	int		ptr_pl;
	int		pl_temp;

	i = -1;
	pl = 0;
	ptr_pl = 0;
	pl_temp = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%' && ft_cset(str[i + 1], "cspdiuxX%"))
			pl += ft_param(args, str[++i], ptr_pl);
		else
			pl += ft_print_char(str[i]);
		if (pl < pl_temp)
			return (va_end(args), -1);
		pl_temp = pl;
	}
	return (va_end(args), pl);
}

int	ft_cset(char s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_param(va_list args, const char format, int pl)
{
	if (format == 'c')
		pl = ft_print_char(va_arg(args, int));
	else if (format == 's')
		pl = ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		pl = ft_print_add(va_arg(args, unsigned long), HL, 1, &pl);
	else if (format == 'd' || format == 'i')
		pl = ft_putnbr_base(va_arg(args, int), D, &pl);
	else if (format == 'u')
		pl = ft_putnbr_base_uns(va_arg(args, unsigned int), D, &pl);
	else if (format == 'x')
		pl = ft_print_add(va_arg(args, unsigned int), HL, 0, &pl);
	else if (format == 'X')
		pl = ft_print_add(va_arg(args, unsigned int), HU, 0, &pl);
	else if (format == '%')
		pl = ft_print_char('%');
	if (pl < 0)
		return (-1);
	return (pl);
}
