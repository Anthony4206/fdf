/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/20 12:43:31 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_push_line(t_running *run, t_point *pix1, t_point *pix2,
	t_bresenham *line)
{
	line = ft_init_bresenham(pix1, pix2);
	if (line->x1 > line->x2)
		line->x_incr = -1;
	if (line->y1 > line->y2)
		line->y_incr = -1;
	if (line->save_dx > line->save_dy)
		ft_first_condition(run, pix1, pix2, line);
	else if (line->save_dx < line->save_dy)
		ft_second_condition(run, pix1, pix2, line);
	else
		ft_exeption(run, pix1, pix2, line);
}

void	ft_draw_lines(t_running *run)
{
	t_bresenham	line;
	int			i;
	int			j;

	ft_calculate_point(run->map, run->map->ri, run->map->vo);
	j = 0;
	while (j < run->map->hgt)
	{
		i = -1;
		while (++i < (run->map->wdt - 1))
			ft_push_line(run, &run->map->v[j][i],
				&run->map->v[j][i + 1], &line);
		j++;
	}
	j = 0;
	while (j < run->map->hgt - 1)
	{
		i = -1;
		while (++i < (run->map->wdt))
			ft_push_line(run, &run->map->v[j][i],
				&run->map->v[j + 1][i], &line);
		j++;
	}
}

int	ft_draw_map(t_running *run)
{
	ft_bzero(run->env.img.addr, WIN_WDT * WIN_HGT * 4);
	ft_draw_lines(run);
	mlx_put_image_to_window(&run->env.mlx, run->env.win,
		run->env.img.img, 0, 0);
	return (0);
}
