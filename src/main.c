/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/06 13:13:16 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_point(t_map *map)
{
	int	i;

	i = 0;
	ft_draw_lines(map);
	mlx_put_image_to_window(&map->mlx, map->win, map->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	char	*path;

	if (argc == 2)
	{
		path = argv[1];
		map = ft_init_map(path);
		map->img.img = mlx_new_image(map->mlx, 3000, 2000);
		map->img.addr = mlx_get_data_addr(map->img.img,
				&map->img.bits_per_pixel, &map->img.line_length,
				&map->img.endian);
		ft_draw_point(map);
		mlx_loop(map->mlx);
		return (0);
	}
	ft_printf("\n");
}
