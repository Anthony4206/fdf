/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:20:04 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/20 12:25:25 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_first_condition(t_running *run, t_point *pix1, t_point *pix2,
	t_bresenham *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dx)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map, 1),
			line->y1 + ft_middle(run->map, 0),
			ft_put_color(pix1, pix2, (float)i / line->save_dx));
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

void	ft_second_condition(t_running *run, t_point *pix1, t_point *pix2,
	t_bresenham *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dy)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map, 1),
			line->y1 + ft_middle(run->map, 0),
			ft_put_color(pix1, pix2, (float)i / line->save_dy));
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

void	ft_exeption(t_running *run, t_point *pix1, t_point *pix2,
	t_bresenham *line)
{
	int	i;
	int	d;

	i = -1;
	d = line->save_dy;
	if (d < line->save_dx)
		d = line->save_dx;
	if (line->save_dx == line->save_dy)
	{
		while (++i <= line->save_dx)
		{
			my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map, 1),
				line->y1 + ft_middle(run->map, 0), ft_put_color(pix1, pix2, (float)i / d));
			line->y1 += line->y_incr;
			line->x1 += line->x_incr;
		}
	}
	else if (line->save_dx == 0 || line->save_dy == 0)
	{
		while (++i <= line->save_dy || i <= line->save_dx)
		{
			my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map, 1),
				line->y1 + ft_middle(run->map, 0), ft_put_color(pix1, pix2, (float)i / d));
			if (line->save_dx == 0)
				line->y1 += line->y_incr;
			else
				line->x1 += line->x_incr;
		}
	}
}