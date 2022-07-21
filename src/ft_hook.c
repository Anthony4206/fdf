#include "fdf.h"

void	ft_perspective(t_pt **v, int p, int i, int j)
{
	v[j][i].x *= p / (p - v[j][i].z);
	v[j][i].y *= p / (p - v[j][i].z);
}

void	ft_zoom(t_map *map, t_geo *geo, float coef)
{
	int		i;
	int		j;

	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			geo->vo[j][i].x *= coef;
			geo->vo[j][i].y *= coef;
			geo->vo[j][i].z *= coef;
			i++;
		}
		j++;
	}
}

void	ft_rotation(int keycode, t_geo *geo)
{
	if (keycode == 0)
		geo->r = ft_multiply_matrix(geo->ri, ft_matrix_rz(0.0974533));
	if (keycode == 1)
		geo->r = ft_multiply_matrix(ft_matrix_rx(0.0974533),geo->ri);
	if (keycode == 2)
		geo->r = ft_multiply_matrix(geo->ri, ft_matrix_rz(-0.0974533));
	if (keycode == 12)
		geo->r = ft_multiply_matrix(ft_matrix_ry(-0.0974533), geo->ri);
	if (keycode == 13)
		geo->r = ft_multiply_matrix(ft_matrix_rx(-0.0974533), geo->ri);
	if (keycode == 14)
		geo->r = ft_multiply_matrix(ft_matrix_ry(0.0974533), geo->ri);
	geo->ri = geo->r;
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
		ft_zoom(run->map, run->map->geo, 1.1);
	if (keycode == 6)
		ft_zoom(run->map, run->map->geo, 0.9);
	if (keycode == 8)
		run->map->cone = 1;
	if (keycode == 11)
		run->map->cone = 0;
	if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 12
		|| keycode == 13 || keycode == 14)
		ft_rotation(keycode, run->map->geo);
	return (0);
}