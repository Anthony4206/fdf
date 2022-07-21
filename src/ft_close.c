#include "fdf.h"

int	ft_close(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
//	system("leaks fdf");
	exit (EXIT_FAILURE);
}
