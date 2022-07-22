/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brez.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:20:04 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 11:04:23 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIN_WDT && y > 0 && y < WIN_HGT)
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	ft_fst_condition(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dx)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map,
				run->map->geo, 1), line->y1 + ft_middle(run->map, run->map->geo,
				0), ft_put_color(pix1, pix2, (float)i / line->save_dx));
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

void	ft_snd_condition(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dy)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map,
				run->map->geo, 1), line->y1 + ft_middle(run->map, run->map->geo,
				0), ft_put_color(pix1, pix2, (float)i / line->save_dy));
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

void	ft_diagonal(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line)
{
	int	i;
	int	d;

	d = line->save_dy;
	if (d < line->save_dx)
		d = line->save_dx;
	i = -1;
	while (++i <= line->save_dx)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map,
				run->map->geo, 1), line->y1 + ft_middle(run->map,
				run->map->geo, 0), ft_put_color(pix1, pix2, (float)i / d));
		line->y1 += line->y_incr;
		line->x1 += line->x_incr;
	}
}

void	ft_exeption(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line)
{
	int	i;
	int	d;

	i = -1;
	d = line->save_dy;
	if (d < line->save_dx)
		d = line->save_dx;
	while (++i <= line->save_dy || i <= line->save_dx)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + ft_middle(run->map,
				run->map->geo, 1), line->y1 + ft_middle(run->map,
				run->map->geo, 0), ft_put_color(pix1, pix2, (float)i / d));
		if (line->save_dx == 0)
			line->y1 += line->y_incr;
		else
			line->x1 += line->x_incr;
	}
}
