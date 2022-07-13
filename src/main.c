/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/12 20:51:03 by Anthony          ###   ########.fr       */
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
		run->map->r = ft_multiply_matrix(run->map->ri, ft_matrix_rz(0.0174533));
	if (keycode == 1)
		run->map->r = ft_multiply_matrix(ft_matrix_rx(0.0174533), run->map->ri);
	if (keycode == 2)
		run->map->r = ft_multiply_matrix(run->map->ri, ft_matrix_rz(-0.0174533));
	if (keycode == 13)
		run->map->r = ft_multiply_matrix(ft_matrix_rx(-0.0174533), run->map->ri);
	if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		run->map->ri = run->map->r;
	if (keycode == 7)
	{
		ft_zoom(run, 1.2);
		printf("%f | %f...\n", run->map->v[6][6].x, run->map->v[6][6].y);
	}
	if (keycode == 6)
		ft_zoom(run, 0.8);
	return (0);
}

void	ft_zoom(t_running *run, float coef)
{
	int		i;
	int		j;

	j = 0;
	printf("Coucou%d\n", run->map->hgt);
	while (j < run->map->hgt)
	{
		i = 0;
		while (i < run->map->wdt)
		{
			run->map->v[j][i].x *= coef;
			run->map->v[j][i].y *= coef;
			run->map->v[j][i].z *= coef;
			i++;
		}
		j++;
	}
}

int	mouse_hook(int keycode, t_running *run)
{
	printf("%d...%d\n", keycode, run->map->hgt);
	if (keycode == 4)
		ft_zoom(run, 1.2);
	if (keycode == 5)
		ft_zoom(run, 0.8);
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