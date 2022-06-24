/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:28 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/24 08:52:13 by alevasse         ###   ########.fr       */
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
			map->coord[(j * map->wdt) + i].x = i * 100;
			map->coord[(j * map->wdt) + i].y = j * 100;
			map->coord[(j * map->wdt) + i].z = ft_atoi(line + k);
			map->coord[(j * map->wdt) + i++].color = 0x00FF0000;
			ft_next_atoi(line, &k);
		}
		free(line);
		line = get_next_line(fd);
	}
	(free (line), close (fd));
}
