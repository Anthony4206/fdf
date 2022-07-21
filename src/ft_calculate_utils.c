/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:03:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 14:06:01 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int j)
{
	if (j < 0)
		j *= -1;
	return (j);
}

int	ft_middle(t_map *map, int opts)
{
	int	ret;

	ret = 0;
	if (opts)
		ret = map->x_origin - (map->v[map->hgt / 2][map->wdt / 2].x - map->v[0][0].x);
	else
		ret = map->y_origin - (map->v[map->hgt / 2][map->wdt / 2].y - map->v[0][0].y);
	return (ret);
}
