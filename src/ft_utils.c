/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:03:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/20 12:09:14 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int j)
{
	if (j < 0)
		j *= -1;
	return (j);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIN_WDT && y > 0 && y < WIN_HGT)
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(int *)dst = color;
	}
}
