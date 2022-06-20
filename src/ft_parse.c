/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:28 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/20 14:43:23 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			map->coord[j][i].x = i;
			map->coord[j][i].y = j;
			map->coord[j][i++].z = ft_atoi(line + k);
			while (ft_isdigit(line[k]))
				k++;
			while (line[k] == ' ')
				k++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free (line);
}
