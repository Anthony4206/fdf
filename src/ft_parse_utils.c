/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:31:07 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 17:15:59 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pt	**ft_alloc_coord(t_map *map)
{
	t_pt	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(map->hgt, sizeof(t_pt *));
	while (i < map->hgt)
	{
		ret[i] = ft_calloc(map->wdt, sizeof(t_pt));
		i++;
	}
	return (ret);
}

int	ft_count_wdt(char *line)
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

int	ft_count_hgt(int fd, char *line)
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

void	ft_next_atoi(char *line, int *k)
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
