/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/23 15:40:21 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_bresenham	ft_init_bresenham(t_point *pix1, t_point *pix2)
{
	t_bresenham	ret;

	ret.x1 = pix1->x;
	ret.x2 = pix2->x;
	ret.y1 = pix1->y;
	ret.y2 = pix2->y;
	ret.ex = ft_abs(ret.x2 - ret.x1);
	ret.ey = ft_abs(ret.y2 - ret.y1);
	ret.dx = 2 * ret.ex;
	ret.dy = 2 * ret.ey;
	ret.x_incr = 1;
	ret.y_incr = 1;
	ret.save_dx = ret.ex;
	ret.save_dy = ret.ey;
	return (ret);
}

static void	ft_first_condition(t_data *img, t_bresenham *line, int color)
{
	int	i;

	i = 0;
	while (i <= line->save_dx)
	{
		my_mlx_pixel_put(img, line->x1, line->y1, color);
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

static void	ft_second_condition(t_data *img, t_bresenham *line, int color)
{
	int	i;

	i = 0;
	while (i <= line->save_dy)
	{
		my_mlx_pixel_put(img, line->x1, line->y1, color);
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

static void	ft_exeption(t_data *img, t_bresenham *line, int color)
{
	int	i;

	i = 0;
	if (line->save_dx == line->save_dy)
	{
		while (i <= line->save_dx)
		{
			my_mlx_pixel_put(img, line->x1, line->y1, color);
			i++;
			line->y1 += line->y_incr;
			line->x1 += line->x_incr;
		}
	}
	else if (line->save_dx == 0)
	{
		while (i <= line->save_dy)
		{
			my_mlx_pixel_put(img, line->x1, line->y1, color);
			i++;
			line->y1 += line->y_incr;
		}
	}
	else if (line->save_dy == 0)
	{
		while (i <= line->save_dx)
		{
			my_mlx_pixel_put(img, line->x1, line->y1, color);
			i++;
			line->x1 += line->x_incr;
		}
	}
}

void	draw_lines(t_data *img, t_map *map, int color)
{
	t_bresenham	line;
	int			i;
	int			j;

	i = 0;
	while (i < map->count)
	{
		while (j < )
		{
			line = ft_init_bresenham(&map->coord[i], &map->coord[i + 1]);
			if (line.x1 > line.x2)
				line.x_incr = -1;
			if (line.y1 > line.y2)
				line.y_incr = -1;
			if (line.save_dx == 0 || line.save_dy == 0
				|| line.save_dx == line.save_dy)
				ft_exeption(img, &line, color);
			else if (line.save_dx > line.save_dy)
				ft_first_condition(img, &line, color);
			else if (line.save_dx < line.save_dy)
				ft_second_condition(img, &line, color);
			j++;
		}
		i++;
	}
}
