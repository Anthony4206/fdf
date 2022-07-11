/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:22:48 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/11 08:16:12 by alevasse         ###   ########.fr       */
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

double	**ft_matrix_ry(t_map *map)
{
	double	**ret;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	ret[0][0] = cos(map->ry);
	ret[0][1] = 0;
	ret[0][2] = sin(map->ry);
	ret[1][0] = 0;
	ret[1][1] = 1;
	ret[1][2] = 0;
	ret[2][0] = -sin(map->ry);
	ret[2][1] = 0;
	ret[2][2] = cos(map->ry);
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

double	**ft_matrix_euler(t_map *map)
{
	double	**ret;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	ret[0][0] = cos(map->rz) * cos(map->ry);
	ret[0][1] = (cos(map->rz) * sin(map->ry) * sin(map->rx)) - (sin(map->rz) * cos(map->rx));
	ret[0][2] = (cos(map->rz) * sin(map->ry) * cos(map->rx)) + (sin(map->rz) * sin(map->rx));
	ret[1][0] = sin(map->rz) * cos(map->ry);
	ret[1][1] = (sin(map->rz) * sin(map->ry) * sin(map->rx)) - (cos(map->rz) * cos(map->rx));
	ret[1][2] = (sin(map->rz) * sin(map->ry) * cos(map->rx)) - (cos(map->rz) * sin(map->rx));
	ret[2][0] = -sin(map->ry);
	ret[2][1] = cos(map->ry) * sin(map->rx);
	ret[2][2] = cos(map->ry) * cos(map->rx);
	return (ret);
}

void	ft_calculate_point(t_map *map, t_point **p)
{
	int		i;
	int		j;
	double	**rx;
//	double	**ry;
	double	**rz;
	double	**m3;

	rx = ft_matrix_rx(map);
//	ry = ft_matrix_ry(map);
	rz = ft_matrix_rz(map);
//	m3 = ft_matrix_euler(map);
	m3 = ft_multiply_matrix(rx, rz);
	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			map->init[j][i].x = p[j][i].x * m3[0][0] + p[j][i].y * m3[0][1] + p[j][i].z * m3[0][2];
			map->init[j][i].y = p[j][i].x * m3[1][0] + p[j][i].y * m3[1][1] + p[j][i].z * m3[1][2];
			map->init[j][i].z = p[j][i].x * m3[2][0] + p[j][i].y * m3[2][1] + p[j][i].z * m3[2][2];
			map->init[j][i].color = 0x00FF0000;
			i++;
		}
		j++;
	}
}
