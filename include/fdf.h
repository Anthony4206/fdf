/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:45 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/23 08:45:52 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_bresenham
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dx;
	int	dy;
	int	ex;
	int	ey;
	int	save_dx;
	int	save_dy;
	int	x_incr;
	int	y_incr;
}		t_bresenham;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef struct s_map
{
	void	*mlx;
	void	*win;
	t_point	*coord;
	int		wdt;
	int		hgt;
	int		count;
	int		max_x;
	int		max_y;
	int		min_z;
	int		max_z;
}			t_map;

int		ft_abs(int j);
void	ft_draw_point(t_map *map, t_data *img);
t_map	*ft_init_map(char *path);
void	ft_parse(int fd, char *path, char *line, t_map *map);
void	draw_line(t_data *img, t_map *map, int color);

#endif