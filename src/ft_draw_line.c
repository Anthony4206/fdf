/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/24 13:57:36 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_first_condition(t_data *img, t_point *pix, t_bresenham *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dx)
	{
		my_mlx_pixel_put(img, line->x1, line->y1, pix->color);
		i++;
		line->x1 += line->x_incr;
		line->ex -= line->dy;
		if (line->ex < 0)
		{
			line->y1 += line->y_incr;
			line->ex += line->dx;
		}
	}
}

static void	ft_second_condition(t_data *img, t_point *pix, t_bresenham *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dy)
	{
		my_mlx_pixel_put(img, line->x1, line->y1, pix->color);
		i++;
		line->y1 += line->y_incr;
		line->ey -= line->dx;
		if (line->ey < 0)
		{
			line->x1 += line->x_incr;
			line->ey += line->dy;
		}
	}
}

static void	ft_exeption(t_data *img, t_point *pix, t_bresenham *line)
{
	int	i;

	i = 0;
	if (line->save_dx == line->save_dy)
	{
		while (i <= line->save_dx)
		{
			my_mlx_pixel_put(img, line->x1, line->y1, pix->color);
			i++;
			line->y1 += line->y_incr;
			line->x1 += line->x_incr;
		}
	}
	else if (line->save_dx == 0 || line->save_dy == 0)
	{
		while (i <= line->save_dy || i <= line->save_dx)
		{
			my_mlx_pixel_put(img, line->x1, line->y1, pix->color);
			if (line->save_dx == 0)
				line->y1 += line->y_incr;
			else
				line->x1 += line->x_incr;
			i++;
		}
	}
}

void	ft_push_line(t_data *img, t_point *pix1, t_point *pix2, t_bresenham *line)
{
	line = ft_init_bresenham(pix1, pix2);
	if (line->x1 > line->x2)
		line->x_incr = -1;
	if (line->y1 > line->y2)
		line->y_incr = -1;
	if (line->save_dx == 0 || line->save_dy == 0
		|| line->save_dx == line->save_dy)
		ft_exeption(img, pix2, line);
	else if (line->save_dx > line->save_dy)
		ft_first_condition(img, pix2, line);
	else if (line->save_dx < line->save_dy)
		ft_second_condition(img, pix2, line);
}

void	ft_draw_lines(t_data *img, t_map *map)
{
	t_bresenham	line;
	int			i;
	int			j;

	j = 0;
	while (j < map->hgt)
	{
		i = -1;
		while (++i < (map->wdt - 1))
			ft_push_line(img, &map->coord[(j * map->wdt) + i],
				&map->coord[(j * map->wdt) + i + 1], &line);
		j++;
	}
	j = 0;
	while (j < map->hgt - 1)
	{
		i = -1;
		while (++i < (map->wdt))
			ft_push_line(img, &map->coord[(j * map->wdt) + i],
				&map->coord[((j + 1) * map->wdt) + i], &line);
		j++;
	}
}
