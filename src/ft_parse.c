/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:28 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/20 12:13:00 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_next_atoi(char *line, int *k)
{
	if (line[0] == '-')
		(*k)++;
	if (line[*k] == '-' && line[*k - 1] == ' ')
		(*k)++;
	if (line[*k] == ',')
		*k += 3;
	while (ft_isdigit(line[*k]) || (line[*k] >= 'a' && line[*k] >= 'f')
		|| (line[*k] >= 'A' && line[*k] >= 'F'))
		(*k)++;
	while (line[*k] == ' ' || line[*k] == '\n')
		(*k)++;
}

double	ft_compute_size(t_map *map)
{
	double	ret_hgt;
	double	ret_wdt;

	ret_wdt = ((WIN_WDT / 20 * 12) / map->wdt);
	ret_hgt = ((WIN_HGT / 20 * 12) / map->hgt);
	if (ret_wdt > ret_hgt)
		return (ret_hgt);
	else
		return (ret_wdt);
}

int	ft_altitude(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
			if (map->vo[j][i].z < map->min_z)
				map->min_z = map->vo[j][i].z;
			if (map->vo[j][i].z > map->max_z)
				map->max_z = map->vo[j][i].z;
			i++;
		}
		j++;
	}
	return (map->max_z - map->min_z);
}

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

void	ft_parse(int fd, char *path, char *line, t_map *map)
{
	int		i;
	int		j;
	int		k;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	j = -1;
	while (++j < map->hgt && line)
	{
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
		free(line);
		line = get_next_line(fd);
	}
	(free (line), close (fd));
}
