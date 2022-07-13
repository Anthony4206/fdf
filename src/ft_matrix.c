/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:22:48 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/12 08:31:13 by Anthony          ###   ########.fr       */
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

double	**ft_matrix_rx(double radian)
{
	double	**ret;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	ret[0][0] = 1;
	ret[0][1] = 0;
	ret[0][2] = 0;
	ret[1][0] = 0;
	ret[1][1] = cos(radian);
	ret[1][2] = -sin(radian);
	ret[2][0] = 0;
	ret[2][1] = sin(radian);
	ret[2][2] = cos(radian);
	return (ret);
}

double	**ft_matrix_rz(double radian)
{
	double	**ret;

	ret = ft_alloc_matrix();
	if (!ret)
		exit (EXIT_FAILURE);
	ret[0][0] = cos(radian);
	ret[0][1] = -sin(radian);
	ret[0][2] = 0;
	ret[1][0] = sin(radian);
	ret[1][1] = cos(radian);
	ret[1][2] = 0;
	ret[2][0] = 0;
	ret[2][1] = 0;
	ret[2][2] = 1;
	return (ret);
}

double	**ft_multiply_matrix(double **m1, double **m2)
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
				ret[i][j] += m1[i][k] * m2[k][j];
		}
	}
	return (ret);
}

void	ft_calculate_point(t_map *map, double **r, t_point **p)
{
	int		i;
	int		j;
	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			map->v[j][i].x = p[j][i].x * r[0][0] + p[j][i].y * r[0][1] + p[j][i].z * r[0][2];
			map->v[j][i].y = p[j][i].x * r[1][0] + p[j][i].y * r[1][1] + p[j][i].z * r[1][2];
			map->v[j][i].z = p[j][i].x * r[2][0] + p[j][i].y * r[2][1] + p[j][i].z * r[2][2];
			map->v[j][i].color = 0x00FF0000;
			i++;
		}
		j++;
	}
}
