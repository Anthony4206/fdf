/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:42:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/23 08:46:10 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_count_wdt(char *line)
{
	int	i;
	int	wdt;

	i = 0;
	wdt = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && (line[i + 1] == ' ' || line[i + 1] == '\n'))
			wdt++;
		i++;
	}
	return (wdt);
}

static int	ft_count_hgt(int fd, char *line)
{
	int	i;
	int	hgt;

	i = 1;
	hgt = 1;
	while (i)
	{
		line = get_next_line(fd);
		if (line == '\0')
			i = 0;
		else
			hgt++;
		free (line);
	}
	return (hgt);
}

t_map	*ft_init_map(char *path)
{
	char	*line;
	int		fd;
	t_map	*ret;

	ret = malloc(sizeof(t_map));
	if (!ret)
		exit (EXIT_FAILURE);
	ret->mlx = mlx_init();
	ret->win = mlx_new_window(ret->mlx, 1920, 1080, "FDF alevasse");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	line = get_next_line(fd);
	ret->wdt = ft_count_wdt(line);
	free (line);
	ret->hgt = ft_count_hgt(fd, line);
	close (fd);
	ret->count = ret->wdt * ret->hgt;
	ret->coord = malloc(sizeof(t_point) * ret->count);
	ft_parse(fd, path, line, ret);
	return (ret);
}
