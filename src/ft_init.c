/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:42:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/22 13:50:34 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_brez	*ft_init_brez(t_pt *pix1, t_pt *pix2)
{
	t_brez	*ret;

	ret = malloc(sizeof(t_brez));
	if (!ret)
		exit (EXIT_FAILURE);
	ret->x1 = pix1->x;
	ret->x2 = pix2->x;
	ret->y1 = pix1->y;
	ret->y2 = pix2->y;
	ret->ex = ft_abs(ret->x2 - ret->x1);
	ret->ey = ft_abs(ret->y2 - ret->y1);
	ret->dx = 2 * ret->ex;
	ret->dy = 2 * ret->ey;
	ret->x_incr = 1;
	ret->y_incr = 1;
	ret->save_dx = ret->ex;
	ret->save_dy = ret->ey;
	return (ret);
}

void	ft_init_color(t_map *map, t_geo *geo)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			if (geo->vo[j][i].color == -1)
				geo->vo[j][i].color = ft_add_color(map, geo->vo[j][i].z);
			i++;
		}
		j++;
	}
}

t_rot	ft_init_rot(void)
{
	t_rot	ret;

	ret.mx1 = ft_matrix_rx(0.0974533);
	ret.my1 = ft_matrix_ry(0.0974533);
	ret.mz1 = ft_matrix_rz(0.0974533);
	ret.mx2 = ft_matrix_rx(-0.0974533);
	ret.my2 = ft_matrix_ry(-0.0974533);
	ret.mz2 = ft_matrix_rz(-0.0974533);
	return (ret);
}

t_geo	*ft_init_geo(t_map *map)
{
	t_geo	*ret;

	ret = malloc(sizeof(t_geo));
	if (!ret)
		exit (EXIT_FAILURE);
	ret->rot = ft_init_rot();
	ret->init_mx = ft_matrix_rx(0.959931);
	ret->init_mz = ft_matrix_rz(0.785398);
	ret->ri = ft_multiply_matrix(ret->init_mx, ret->init_mz);
	ret->r = ft_alloc_matrix();
	ret->vo = ft_alloc_coord(map);
	ret->v = ft_alloc_coord(map);
	return (ret);
}

t_map	*ft_init_map(char *path)
{
	char	*line;
	int		fd;
	t_map	*ret;

	ret = malloc(sizeof(t_map));
	if (!ret)
		exit (EXIT_FAILURE);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	line = get_next_line(fd);
	ft_init_size(fd, line, ret);
	ret->count = ret->wdt * ret->hgt;
	ret->x_origin = WIN_WDT / 2;
	ret->y_origin = WIN_HGT / 2;
	ret->min_z = 0;
	ret->max_z = 0;
	ret->cone = 0;
	ret->space = ft_compute_size(ret);
	ret->geo = ft_init_geo(ret);
	ft_parse(fd, path, line, ret);
	ret->alt = ft_altitude(ret, ret->geo);
	ft_init_color(ret, ret->geo);
	ft_add_z(ret, ret->geo);
	return (ret);
}
