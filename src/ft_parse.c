/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:28 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/22 13:46:26 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_size(int fd, char *line, t_map *map)
{
	map->wdt = ft_count_wdt(line);
	free (line);
	map->hgt = ft_count_hgt(fd, line);
	close (fd);
}

int	ft_altitude(t_map *map, t_geo *geo)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			if (geo->vo[j][i].z < map->min_z)
				map->min_z = geo->vo[j][i].z;
			if (geo->vo[j][i].z > map->max_z)
				map->max_z = geo->vo[j][i].z;
			i++;
		}
		j++;
	}
	return (map->max_z - map->min_z);
}

void	ft_add_z(t_map *map, t_geo *geo)
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
			geo->vo[j][i].z *= coef;
			i++;
		}
		j++;
	}
}

void	ft_add_coord(char *line, t_map *map, t_geo *geo, int j)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (++i < map->wdt && line[k])
	{
		geo->vo[j][i].x = i * map->space;
		geo->vo[j][i].y = j * map->space;
		geo->vo[j][i].z = ft_atoi(line + k);
		ft_next_atoi(line, &k);
		if (line[k] == ',')
		{
			geo->vo[j][i].color = ft_htoi(line + k);
			ft_next_atoi(line, &k);
		}
		else
			geo->vo[j][i].color = -1;
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
		ft_add_coord(line, map, map->geo, j);
		free(line);
		line = get_next_line(fd);
	}
	(free (line), close (fd));
}
