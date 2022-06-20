/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/11 11:00:14 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	first_condition(t_data *img, int incr, t_bresenham pix)
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

static void	second_condition(t_data *img, int incr, t_bresenham pix)
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

void	draw_line(t_data *img, int *x, int *y, int color)
{
// Traiter les cas : dx2 = 0 ; dy2 = 0 ; dx2 == dy2 ; Initialisation des structures
	t_bresenham	pix;
	t_point		pts
	int			i;
	
	i = 0;
	pix.x1 = pts->x;
	pix.x2 = pts->x;
	pix.y1 = pts->;
	pix.y2 = pts->;
	pix.ex = ft_abs(x2 - x1);
	pix.ey = ft_abs(y2 - y1);
	pix.dx = 2 * ex;
	pix.dy = 2 * ey;
	pix.x_incr = 1;
	pix.y_incr = 1;
	pix.dx2 = ex;
	pix.dy2 = ey;
	if (x1 > x2)
		x_incr = -1;
	if (y1 > y2)
		y_incr = -1;
}