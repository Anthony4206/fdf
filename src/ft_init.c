/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:42:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/12 14:47:01 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_count_wdt(char *line)
{
	int	i;
	int	wdt;

	i = 0;
	wdt = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && (line[i + 1] == ' ' || line[i + 1] == '\n'))
			wdt++;
		i++;
	}
	return (wdt);
}

static int	ft_count_hgt(int fd, char *line)
{
	int	i;
	int	hgt;

	i = 1;
	hgt = 1;
	while (i)
	{
		line = get_next_line(fd);
		if (line == '\0')
			i = 0;
		else
			hgt++;
		free (line);
	}
	return (hgt);
}

t_bresenham	*ft_init_bresenham(t_point *pix1, t_point *pix2)
{
	t_bresenham	*ret;

	ret = malloc(sizeof(t_bresenham));
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

t_point	**ft_init_coord(t_map *map)
{
	t_point	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(map->hgt, sizeof(t_point *));
	while (i < map->hgt)
	{
		ret[i] = ft_calloc(map->wdt, sizeof(t_point));
		i++;
	}
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
	ret->wdt = ft_count_wdt(line);
	free (line);
	ret->hgt = ft_count_hgt(fd, line);
	close (fd);
	ret->count = ret->wdt * ret->hgt;
	ret->mx = ft_matrix_rx(0.959931);
	ret->my = 0;
	ret->mz = ft_matrix_rz(0.785398);
	ret->space = ft_compute_size(ret);
	ret->vo = ft_init_coord(ret);
	ret->v = ft_init_coord(ret);
	ret->ri = ft_multiply_matrix(ret->mx, ret->mz);
	ret->r = ft_alloc_matrix();
	ret->offset_hgt = 100;
	ret->offset_wdt = 250;
	ft_parse(fd, path, line, ret);
	return (ret);
}