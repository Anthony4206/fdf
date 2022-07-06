/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:45 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/06 13:10:37 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define WIN_WDT 1920
# define WIN_HGT 1080

typedef struct s_quaternion
{
	double	w;
	double	x;
	double	y;
	double	z;
	double	cy;
	double	sy;
	double	cp;
	double	sp;
	double	cr;
	double	sr;
}			t_quaternion;

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
	int	w;
	int	color;
}		t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	void	*mlx;
	void	*win;
	t_point	**coord;
	t_point	**rotate;
	t_data	img;
	int		x_origin;
	int		y_origin;
	int		offset_hgt;
	int		offset_wdt;
	int		wdt;
	int		hgt;
	int		count;
	int		color;
	int		space;
	double	rx;
	double	ry;
	double	rz;
}			t_map;

/*typedef struct
{
	t_map	map;
	
}	t_runtime;*/

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				ft_abs(int j);
void			ft_draw_point(t_map *map);
t_map			*ft_init_map(char *path);
void			ft_parse(int fd, char *path, char *line, t_map *map);
void			ft_draw_lines(t_map *map);
t_bresenham		*ft_init_bresenham(t_point *pix1, t_point *pix2);
t_quaternion	*ft_init_quaternion(double yaw, double pitch, double roll);
void			ft_calculate_point(t_map *map, t_point **s);
t_point			**ft_init_coord(t_map *map);

#endif
