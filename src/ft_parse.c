/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:28 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/27 08:16:09 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_next_atoi(char *line, int *k)
{
	if (line[0] == '-')
		(*k)++;
	if (line[*k] == '-' && line[*k - 1] == ' ')
		(*k)++;
	while (ft_isdigit(line[*k]))
		(*k)++;
	while (line[*k] == ' ' || line[*k] == '\n')
		(*k)++;
}

double	ft_compute_size(t_map *map)
{
	double	ret_hgt;
	double	ret_wdt;

	ret_wdt = ((WIN_WDT / 20 * 18) / map->wdt);
	ret_hgt = ((WIN_HGT / 20 * 18) / map->hgt);
	if (ret_wdt > ret_hgt)
		return (ret_hgt);
	else
		return (ret_wdt);
}

void	ft_parse(int fd, char *path, char *line, t_map *map)
{
	int		i;
	int		j;
	int		k;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	j = -1;
	while (j++, line)
	{
		i = 0;
		k = 0;
		while (line[k])
		{
			map->coord[(j * map->wdt) + i].x = i * ft_compute_size(map);
			map->coord[(j * map->wdt) + i].y = j * ft_compute_size(map);
			map->coord[(j * map->wdt) + i].z = ft_atoi(line + k);
			map->coord[(j * map->wdt) + i++].color = 0x00FF0000;
			ft_next_atoi(line, &k);
		}
		free(line);
		line = get_next_line(fd);
	}
	(free (line), close (fd));
	map->offset_hgt = ((WIN_HGT - ((map->hgt - 1) * ft_compute_size(map))) / 2);
	map->offset_wdt = ((WIN_WDT - ((map->wdt - 1) * ft_compute_size(map))) / 2);
}
