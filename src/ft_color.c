/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 06:33:57 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 15:19:14 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_add_color(t_map *map, double z)
{
	double	coef;

	if (map->max_z == 0)
		map->max_z = 1;
	if (z >= 0)
		coef = -(128 / map->max_z);
	else
		coef = (128 / map->min_z);
	return (ft_create_trgb(0, 255, 128 + (coef * z), 0));
}

int	ft_put_color(t_pt *pix1, t_pt *pix2, float pct)
{
	return (ft_create_trgb(0,
			degrad(get_r(pix1->color), get_r(pix2->color), pct),
			degrad(get_g(pix1->color), get_g(pix2->color), pct),
			degrad(get_b(pix1->color), get_b(pix2->color), pct)));
}
