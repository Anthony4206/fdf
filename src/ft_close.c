/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:23 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/22 12:56:26 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_matrix(double **m)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		free(m[i]);
		i++;
	}
	free(m);
}

int	ft_close(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	system("leaks fdf");
	exit (EXIT_SUCCESS);
}
