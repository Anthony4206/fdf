#include "fdf.h"

void	ft_zoom(t_run *run, float coef)
{
	int		i;
	int		j;

	j = 0;
	while (j < run->map->hgt)
	{
		i = 0;
		while (i < run->map->wdt)
		{
			run->map->vo[j][i].x *= coef;
			run->map->vo[j][i].y *= coef;
			run->map->vo[j][i].z *= coef;
			i++;
		}
		j++;
	}
}

void	ft_rotation(int keycode, t_run *run)
{
	if (keycode == 0)
		run->map->r = ft_multiply_matrix(run->map->ri, ft_matrix_rz(0.0974533));
	if (keycode == 1)
		run->map->r = ft_multiply_matrix(ft_matrix_rx(0.0974533), run->map->ri);
	if (keycode == 2)
		run->map->r = ft_multiply_matrix(run->map->ri, ft_matrix_rz(-0.0974533));
	if (keycode == 12)
		run->map->r = ft_multiply_matrix(ft_matrix_ry(-0.0974533), run->map->ri);
	if (keycode == 13)
		run->map->r = ft_multiply_matrix(ft_matrix_rx(-0.0974533), run->map->ri);
	if (keycode == 14)
		run->map->r = ft_multiply_matrix(ft_matrix_ry(0.0974533), run->map->ri);
	run->map->ri = run->map->r;
}

int	key_hook(int keycode, t_run *run)
{
	if (keycode == 123)
		run->map->x_origin -= 50;
	if (keycode == 124)
		run->map->x_origin += 50;
	if (keycode == 125)
		run->map->y_origin += 50;
	if (keycode == 126)
		run->map->y_origin -= 50;
	if (keycode == 7)
		ft_zoom(run, 1.1);
	if (keycode == 6)
		ft_zoom(run, 0.9);
	if (keycode == 8)
		run->map->cone = 1;
	if (keycode == 11)
		run->map->cone = 0;
	if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 12
		|| keycode == 13 || keycode == 14)
		ft_rotation(keycode, run);
	return (0);
}