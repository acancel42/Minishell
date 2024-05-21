/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acancel <acancel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:39:13 by acancel           #+#    #+#             */
/*   Updated: 2024/01/12 13:53:30 by acancel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_add(unsigned long nbr, char *base, int ox, int *pl)
{
	size_t	blen;

	blen = 0;
	if (base == NULL)
		return (0);
	blen = ft_strlen_ft_printf(base);
	if (ox == 1)
	{
		if (nbr == 0)
		{
			ox = 0;
			return (ft_print_str("(nil)"));
		}
		*pl = ft_print_str("0x");
		ox = 0;
	}
	if (nbr > (unsigned long)(blen - 1))
		ft_print_add(nbr / (blen), base, ox, pl);
	*pl += ft_print_char(base[nbr % (blen)]);
	return (*pl);
}

int	ft_putnbr_base(long nbr, char *base, int *pl)
{
	size_t	blen;

	blen = 0;
	if (base == NULL)
		return (0);
	blen = ft_strlen_ft_printf(base);
	if (nbr < 0)
	{
		nbr = -nbr;
		*pl = ft_print_char('-');
	}
	if (nbr > (long)(blen - 1))
		ft_putnbr_base(nbr / (blen), base, pl);
	*pl += ft_print_char(base[nbr % (blen)]);
	return (*pl);
}

int	ft_putnbr_base_uns(unsigned int nbr, char *base, int *pl)
{
	size_t	blen;

	blen = 0;
	if (base == NULL)
		return (0);
	blen = ft_strlen_ft_printf(base);
	if (nbr > (unsigned int)(blen - 1))
		ft_putnbr_base(nbr / (blen), base, pl);
	*pl += ft_print_char(base[nbr % (blen)]);
	return (*pl);
}
