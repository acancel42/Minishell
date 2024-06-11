/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibert <talibert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:46:56 by acancel           #+#    #+#             */
/*   Updated: 2024/06/10 17:15:34 by talibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isoperator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
int	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}
