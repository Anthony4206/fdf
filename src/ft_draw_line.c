/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/10 22:15:12 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_first_condition(t_running *run, t_point *pix, t_bresenham *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dx)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + run->map->offset_wdt,
			line->y1 + run->map->offset_hgt, pix->color);
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

static void	ft_second_condition(t_running *run, t_point *pix, t_bresenham *line)
{
	int	i;

	i = 0;
	while (i <= line->save_dy)
	{
		my_mlx_pixel_put(&run->env.img, line->x1 + run->map->offset_wdt,
			line->y1 + run->map->offset_hgt, pix->color);
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

static void	ft_exeption(t_running *run, t_point *pix, t_bresenham *line)
{
	int	i;

	i = -1;
	if (line->save_dx == line->save_dy)
	{
		while (++i <= line->save_dx)
		{
			my_mlx_pixel_put(&run->env.img, line->x1 + run->map->offset_wdt,
				line->y1 + run->map->offset_hgt, pix->color);
			line->y1 += line->y_incr;
			line->x1 += line->x_incr;
		}
	}
	else if (line->save_dx == 0 || line->save_dy == 0)
	{
		while (++i <= line->save_dy || i <= line->save_dx)
		{
			my_mlx_pixel_put(&run->env.img, line->x1 + run->map->offset_wdt,
				line->y1 + run->map->offset_hgt, pix->color);
			if (line->save_dx == 0)
				line->y1 += line->y_incr;
			else
				line->x1 += line->x_incr;
		}
	}
}

void	ft_push_line(t_running *run, t_point *pix1, t_point *pix2,
	t_bresenham *line)
{
	line = ft_init_bresenham(pix1, pix2);
	if (line->x1 > line->x2)
		line->x_incr = -1;
	if (line->y1 > line->y2)
		line->y_incr = -1;
	if (line->save_dx == 0 || line->save_dy == 0
		|| line->save_dx == line->save_dy)
		ft_exeption(run, pix2, line);
	else if (line->save_dx > line->save_dy)
		ft_first_condition(run, pix2, line);
	else if (line->save_dx < line->save_dy)
		ft_second_condition(run, pix2, line);
}

int	ft_draw_map(t_running *run)
{
	run->env.img.img = mlx_new_image(run->env.mlx, 1280, 800);
	run->env.img.addr = mlx_get_data_addr(run->env.img.img, &run->env.img.bpp,
			&run->env.img.line_len, &run->env.img.endian);
//	ft_bzero(run->env.img.addr, 1280 * 1080 * 2);
	ft_draw_lines(run);
	mlx_put_image_to_window(&run->env.mlx, run->env.win,
		run->env.img.img, 0, 0);
		return (0);
}

void	ft_draw_lines(t_running *run)
{
	t_bresenham	line;
	int			i;
	int			j;

	ft_calculate_point(run->map, run->map->parse);

	j = 0;
	while (j < run->map->hgt)
	{
		i = -1;
		while (++i < (run->map->wdt - 1))
			ft_push_line(run, &run->map->init[j][i],
				&run->map->init[j][i + 1], &line);
		j++;
	}
	j = 0;
	while (j < run->map->hgt - 1)
	{
		i = -1;
		while (++i < (run->map->wdt))
			ft_push_line(run, &run->map->init[j][i],
				&run->map->init[j + 1][i], &line);
		j++;
	}
}
