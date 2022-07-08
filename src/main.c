/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/08 13:39:13 by alevasse         ###   ########.fr       */
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
	ft_printf("Coucou %d\n", keycode);
	if (keycode == 124)
	{
		run->map->offset_wdt += 50;
		ft_draw_map(run);
	}
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
	run.env.img.img = mlx_new_image(run.env.mlx, 1980, 1080);
	run.env.img.addr = mlx_get_data_addr(run.env.img.img, &run.env.img.bpp,
			&run.env.img.line_len, &run.env.img.endian);
	mlx_hook(run.env.win, 17, 0, ft_close, &run.env);
	ft_draw_map(&run);
	mlx_key_hook(run.env.win, key_hook, &run);
	mlx_loop_hook(run.env.mlx, render_next_frame, YourStruct);
	mlx_loop(run.env.mlx);
	return (0);
}
