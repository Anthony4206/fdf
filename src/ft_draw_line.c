/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/23 07:58:18 by Anthony          ###   ########.fr       */
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
}

static void	ft_first_condition(t_data *img, int incr, t_bresenham pix)
{
	if (dx2 > dy2)
	{
		while (i <= dx2)
		{
			my_mlx_pixel_put(img, x1, y1, color);
			i++;
			x1 += x_incr;
			ex -= dy;
			if (ex < 0)
			{
				y1 += y_incr;
				ex += dx;
			}
		}
	}
}

static void	ft_second_condition(t_data *img, int incr, t_bresenham pix)
{
	if (dx2 < dy2)
	{
		while (i <= dy2)
		{
			my_mlx_pixel_put(img, x1, y1, color);
			i++;
			y1 += y_incr;
			ey -= dx;
			if (ey < 0)
			{
				x1 += x_incr;
				ey += dy;
			}
		}
	}
}

void	draw_line(t_data *img, t_map *map, int color)
{
// Traiter les cas : dx2 = 0 ; dy2 = 0 ; dx2 == dy2 ; Initialisation des structures
	t_bresenham	line;
	int			i;
	
	i = 0;
	ft_init_bresenham(map->coord[])
	if (x1 > x2)
		x_incr = -1;
	if (y1 > y2)
		y_incr = -1;
}
