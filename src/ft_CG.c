/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_CG.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:22:48 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/08 11:18:22 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	**ft_alloc_matrix(void)
{
	double	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(3, sizeof(double *));
	while (i < 3)
	{
		ret[i] = ft_calloc(3, sizeof(double));
		i++;
	}
	return (ret);
}

double	**ft_matrix_rx(t_map *map)
{
	double	**ret;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	ret[0][0] = 1;
	ret[0][1] = 0;
	ret[0][2] = 0;
	ret[1][0] = 0;
	ret[1][1] = cos(map->rx);
	ret[1][2] = -sin(map->rx);
	ret[2][0] = 0;
	ret[2][1] = sin(map->rx);
	ret[2][2] = cos(map->rx);
	return (ret);
}

double	**ft_matrix_rz(t_map *map)
{
	double	**ret;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	ret[0][0] = cos(map->rz);
	ret[0][1] = -sin(map->rz);
	ret[0][2] = 0;
	ret[1][0] = sin(map->rz);
	ret[1][1] = cos(map->rz);
	ret[1][2] = 0;
	ret[2][0] = 0;
	ret[2][1] = 0;
	ret[2][2] = 1;
	return (ret);
}

double	**ft_multiply_matrix(double **rx, double **rz)
{
	double	**ret;
	int		i;
	int		j;
	int		k;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			while (++k < 3)
				ret[i][j] += rx[i][k] * rz[k][j];
		}
	}
	return (ret);
}

void	ft_calculate_point(t_map *map, t_point **s)
{
	int		i;
	int		j;
	double	**rx;
	double	**rz;
	double	**m3;

	rx = ft_matrix_rx(map);
	rz = ft_matrix_rz(map);
	m3 = ft_multiply_matrix(rx, rz);
	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			map->init[j][i].x = s[j][i].x * m3[0][0] + s[j][i].y * m3[0][1] + s[j][i].z * m3[0][2];
			map->init[j][i].y = s[j][i].x * m3[1][0] + s[j][i].y * m3[1][1] + s[j][i].z * m3[2][1];
			map->init[j][i].z = s[j][i].x * m3[2][0] + s[j][i].y * m3[2][1] + s[j][i].z * m3[2][2];
			map->init[j][i].color = 0x00FF0000;
			i++;
		}
		j++;
	}
}
