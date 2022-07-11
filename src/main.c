/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/10 22:16:01 by Anthony          ###   ########.fr       */
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
	ft_draw_map(run);
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
	mlx_hook(run.env.win, 2, 1L << 0, key_hook, &run);
	ft_draw_map(&run);
	mlx_loop_hook(run.env.mlx, ft_draw_map, &run);
	mlx_hook(run.env.win, 17, 0, ft_close, &run.env);
	mlx_loop(run.env.mlx);
	return (0);
}
