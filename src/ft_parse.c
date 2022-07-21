/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:28 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 15:00:17 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_add_z(t_map *map)
{
	int		i;
	int		j;
	double	coef;

	if (map->alt < 7)
		coef = 10;
	else if (map->alt >= 7 && map->alt < 16)
		coef = 5;
	else if (map->alt >= 16 && map->alt < 21)
		coef = 2;
	else if (map->alt >= 21 && map->alt < 73)
		coef = 0.7;
	else
		coef = 0.2;
	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			map->vo[j][i].z *= coef;
			i++;
		}
		j++;
	}
}

void	ft_add_coord(char *line, t_map *map, int j)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (++i < map->wdt && line[k])
	{
		map->vo[j][i].x = i * map->space;
		map->vo[j][i].y = j * map->space;
		map->vo[j][i].z = ft_atoi(line + k);
		ft_next_atoi(line, &k);
		if (line[k] == ',')
		{
			map->vo[j][i].color = ft_htoi(line + k);
			ft_next_atoi(line, &k);
		}
		else
			map->vo[j][i].color = -1;
	}
}

void	ft_parse(int fd, char *path, char *line, t_map *map)
{
	int		j;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	j = -1;
	while (++j < map->hgt && line)
	{
		ft_add_coord(line, map, j);
		free(line);
		line = get_next_line(fd);
	}
	(free (line), close (fd));
}
