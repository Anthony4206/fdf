/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:42:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/27 07:59:38 by alevasse         ###   ########.fr       */
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

/*t_quaternion	ft_init_quaternion(double yaw, double pitch, double roll)
{
	t_quaternion	*q;

	q = malloc(sizeof(t_quaternion));
	if (!q)
		exit (EXIT_FAILURE);
	q->cy = cos();
	q->sy = sin();
	q->cp = cos();
	q->sp = sin();
	q->cr = sin();
	q->sr = cos();
}*/

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

t_map	*ft_init_map(char *path)
{
	char	*line;
	int		fd;
	t_map	*ret;

	ret = malloc(sizeof(t_map));
	if (!ret)
		exit (EXIT_FAILURE);
	ret->mlx = mlx_init();
	ret->win = mlx_new_window(ret->mlx, WIN_WDT, WIN_HGT, "FDF alevasse");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	line = get_next_line(fd);
	ret->wdt = ft_count_wdt(line);
	free (line);
	ret->hgt = ft_count_hgt(fd, line);
	close (fd);
	ret->count = ret->wdt * ret->hgt;
	ret->color = 0x00FF0000;
	ret->coord = malloc(sizeof(t_point) * ret->count);
	ft_parse(fd, path, line, ret);
	return (ret);
}
