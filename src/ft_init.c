/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:42:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 15:19:14 by Anthony          ###   ########.fr       */
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

void	ft_init_color(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			if (map->vo[j][i].color == -1)
				map->vo[j][i].color = ft_add_color(map, map->vo[j][i].z);
			i++;
		}
		j++;
	}
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
	ret->wdt = ft_count_wdt(line);
	free (line);
	ret->hgt = ft_count_hgt(fd, line);
	close (fd);
	ret->count = ret->wdt * ret->hgt;
	ret->x_origin = WIN_WDT / 2;
	ret->y_origin = WIN_HGT / 2;
	ret->min_z = 0;
	ret->max_z = 0;
	ret->mx = ft_matrix_rx(0.959931);
	ret->my = 0;
	ret->mz = ft_matrix_rz(0.785398);
	ret->cone = 0;
	ret->space = ft_compute_size(ret);
	ret->vo = ft_alloc_coord(ret);
	ret->v = ft_alloc_coord(ret);
	ret->ri = ft_multiply_matrix(ret->mx, ret->mz);
	ret->r = ft_alloc_matrix();
	ret->offset_hgt = 100;
	ret->offset_wdt = 250;
	ft_parse(fd, path, line, ret);
	ret->alt = ft_altitude(ret);
	ft_init_color(ret);
	ft_add_z(ret);
	return (ret);
}
