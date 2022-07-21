/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 22:51:11 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_push_line(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line)
{
	line = ft_init_brez(pix1, pix2);
	if (line->x1 > line->x2)
		line->x_incr = -1;
	if (line->y1 > line->y2)
		line->y_incr = -1;
	if (line->save_dx > line->save_dy)
		ft_fst_condition(run, pix1, pix2, line);
	else if (line->save_dx < line->save_dy)
		ft_snd_condition(run, pix1, pix2, line);
	else if (line->save_dx == line->save_dy)
		ft_diagonal(run, pix1, pix2, line);
	else
		ft_exeption(run, pix1, pix2, line);
}

void	ft_calculate_point(t_map *map, double **r, t_pt **v, t_pt **vo)
{
	int		i;
	int		j;
	int		p;

	if (map->wdt > map->hgt)
		p = map->space * (30 + map->wdt);
	else
		p = map->space * (30 + map->hgt);
	j = -1;
	while (++j < map->hgt)
	{
		i = -1;
		while (++i < map->wdt)
		{
			v[j][i].x = vo[j][i].x * r[0][0] + vo[j][i].y * r[0][1]
				+ vo[j][i].z * r[0][2];
			v[j][i].y = vo[j][i].x * r[1][0] + vo[j][i].y * r[1][1]
				+ vo[j][i].z * r[1][2];
			v[j][i].z = vo[j][i].x * r[2][0] + vo[j][i].y * r[2][1]
				+ vo[j][i].z * r[2][2];
			if (map->cone)
				ft_perspective(v, p, i, j);
			v[j][i].color = vo[j][i].color;
		}
	}
}

void	ft_draw_lines(t_run *run, t_map *map, t_geo *geo)
{
	t_brez	line;
	int			i;
	int			j;

	ft_calculate_point(map, geo->ri, geo->v, geo->vo);
	j = 0;
	while (j < map->hgt)
	{
		i = -1;
		while (++i < (map->wdt - 1))
			ft_push_line(run, &map->geo->v[j][i],
				&map->geo->v[j][i + 1], &line);
		j++;
	}
	j = 0;
	while (j < run->map->hgt - 1)
	{
		i = -1;
		while (++i < (run->map->wdt))
			ft_push_line(run, &map->geo->v[j][i],
				&map->geo->v[j + 1][i], &line);
		j++;
	}
}

int	ft_draw_map(t_run *run)
{
	ft_bzero(run->env.img.addr, WIN_WDT * WIN_HGT * 4);
	ft_draw_lines(run, run->map, run->map->geo);
	mlx_put_image_to_window(&run->env.mlx, run->env.win,
		run->env.img.img, 0, 0);
	return (0);
}
