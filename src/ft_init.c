/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:42:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/20 14:53:20 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_wdt(char *line)
{
	int	i;
	int	wdt;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			wdt++;
		i++;
	}
	return (wdt);
}

/*int	ft_count_hgt(int fd, char *line)
{
	int	i;
	int	hgt;

	i = 0;
	hgt = 1;
	line = get_next_line(fd);
	while (line)
	{
		hgt++;
		free (line);
		line = get_next_line(fd);
	}
	free (line);
}*/

int	ft_count_hgt(int fd, char *line)
{
	int	i;
	int	hgt;

	i = 1;
	hgt = 1;
	while (i)
	{
		hgt++;
		line = get_next_line(fd);
		if (line == '\0')
			i = 0;
		else
			hgt++;
		free (line);
	}
}

void	ft_init_map(char *path, t_map *map)
{
	char	*line;
	int		fd;

	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 1920, 1080, "FDF alevasse");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	map->wdt = ft_count_wdt(line);
	free (line);
	map->hgt = ft_count_hgt(fd, line);
	close (fd);
	map->coord = malloc(sizeof(t_point *) * (map->wdt * map->hgt) + 1);
	ft_parse(fd, path, line, map);
}
