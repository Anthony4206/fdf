/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/22 10:42:33 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_run	run;
	char	*path;

	if (argc != 2)
		exit (EXIT_FAILURE);
	path = argv[1];
	run.map = ft_init_map(path);
	run.env.mlx = mlx_init();
	run.env.win = mlx_new_window(run.env.mlx, WIN_WDT, WIN_HGT, "FDF");
	run.env.img.img = mlx_new_image(run.env.mlx, WIN_WDT, WIN_HGT);
	run.env.img.addr = mlx_get_data_addr(run.env.img.img, &run.env.img.bpp,
			&run.env.img.line_len, &run.env.img.endian);
	ft_draw_map(&run);
	mlx_hook(run.env.win, 17, 0, ft_close, &run.env);
	mlx_hook(run.env.win, 2, 1L << 0, key_hook, &run);
	mlx_loop_hook(run.env.mlx, ft_draw_map, &run);
	mlx_loop(run.env.mlx);
	return (0);
}
