/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/11 11:57:21 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit (EXIT_FAILURE);
}

int	key_hook(int keycode, t_running *run)
{
	ft_printf("%d\n", keycode);
	if (keycode == 123 && run->map->offset_wdt > -200)
		run->map->offset_wdt -= 50;
	if (keycode == 124 && run->map->offset_wdt < 1000)
		run->map->offset_wdt += 50;
	if (keycode == 125 && run->map->offset_hgt < 1000)
		run->map->offset_hgt += 50;
	if (keycode == 126 && run->map->offset_hgt > -200)
		run->map->offset_hgt -= 50;
	if (keycode == 0)
		run->map->rz += 0.0174533;
	if (keycode == 1)
		run->map->rx += 0.0174533;
	if (keycode == 2)
		run->map->rz -= 0.0174533;
	if (keycode == 13)
		run->map->rx -= 0.0174533;
	if (keycode == 15)
		run->map->space += 2;
	if (keycode == 3)
		run->map->space -= 2;
	ft_draw_map(run);
	return (0);
}

int	mouse_hook(int keycode, t_running *run)
{
	(void) run;
	printf("%d...\n", keycode);
	if (keycode == 4)
		run->map->space += 2;
	if (keycode == 5) {
		printf("lol\n");
	}
//		run->map->space -= 2;
	//ft_draw_map(run);
	return (0);
}

int	main(int argc, char **argv)
{
	t_running	run;
	char		*path;

	if (argc != 2)
		exit (EXIT_FAILURE);
	path = argv[1];
	run.map = ft_init_map(path);
	run.env.mlx = mlx_init();
	run.env.win = mlx_new_window(run.env.mlx, WIN_WDT, WIN_HGT, "FDF");
	run.env.img.img = mlx_new_image(run.env.mlx, WIN_WDT, WIN_HGT);
	run.env.img.addr = mlx_get_data_addr(run.env.img.img, &run.env.img.bpp,
			&run.env.img.line_len, &run.env.img.endian);

	mlx_hook(run.env.win, 2, 1L << 0, key_hook, &run);
	mlx_mouse_hook(run.env.win, mouse_hook, &run);
	ft_draw_map(&run);
	mlx_loop_hook(run.env.mlx, ft_draw_map, &run);
	mlx_hook(run.env.win, 17, 0, ft_close, &run.env);
	mlx_loop(run.env.mlx);
	return (0);
}
