/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 08:50:44 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/20 06:51:48 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_base(int c)
{
	char	*index_low;
	char	*index_up;
	int		i;

	index_low = "0123456789abcdef";
	index_up = "0123456789ABCDEF";
	i = 0;
	while (i < 16)
	{
		if (index_low[i] == c || index_up[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_htoi(const char *str)
{
	int		i;
	int		res;

	i = 3;
	res = 0;
	while (str[i] && ft_base(str[i]) != -1)
	{
		res *= 16;
		res += ft_base(str[i]);
		i++;
	}
	return (res);
}
