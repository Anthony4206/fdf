/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:03:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 16:55:11 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int j)
{
	if (j < 0)
		j *= -1;
	return (j);
}

int	ft_middle(t_map *map, t_geo *geo, int opts)
{
	int	ret;

	ret = 0;
	if (opts)
		ret = map->x_origin - (geo->v[map->hgt / 2][map->wdt / 2].x - geo->v[0][0].x);
	else
		ret = map->y_origin - (geo->v[map->hgt / 2][map->wdt / 2].y - geo->v[0][0].y);
	return (ret);
}
