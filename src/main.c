/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/23 09:07:48 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*void	draw_line(t_data *img, t_point *a, int *b, int color)
{
// Traiter les cas : dx2 = 0 ; dy2 = 0 ; dx2 == dy2 ; Initialisation des structures
	int	dy;
	int	ex;
	int	ey;
	int x_incr;
	int y_incr;
	int	i;
	int	dx2;
	int	dy2;
	W = 0;
	H = 0;
	x1 = 0;
	x2 = 80;
	y1 = 80;
	y2 = 30;
	ex = abs(x2 - x1);
	ey = abs(y2 - y1);
	dx = 2 * ex;
	dy = 2 * ey;
	x_incr = 1;
	y_incr = 1;
	i = 0;
	dx2 = ex;
	dy2 = ey;
	if (x1 > x2)
		x_incr = -1;
	if (y1 > y2)
		y_incr = -1;
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
}*/

void	ft_draw_point(t_map *map, t_data *img)
{
	int	i;

	i = 0;
	while (i < map->count)
	{
		my_mlx_pixel_put(img, map->coord[i].x, map->coord[i].y, 0x00FF0000);
		i++;
	}
	draw_lines(img, map, 0x00FF0000);
	mlx_put_image_to_window(map->mlx, map->win, img->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	img;
	char	*path;

	if (argc == 2)
	{
		path = argv[1];
		map = ft_init_map(path);
		img.img = mlx_new_image(map->mlx, 1920, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		ft_draw_point(map, &img);
		mlx_loop(map->mlx);
		return (0);
	}
	ft_printf("\n");
}
