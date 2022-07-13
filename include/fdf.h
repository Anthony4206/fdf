/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:45 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/12 17:34:01 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define WIN_WDT 1280
# define WIN_HGT 800

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
	double	x;
	double	y;
	double	z;
	int		color;
}			t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_data;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_data	img;

}			t_env;

typedef struct s_map
{
	t_point	**vo;
	t_point	**v;
	t_point	**rotate;
	double	**ri;
	double	**r;
	int		x_origin;
	int		y_origin;
	int		offset_hgt;
	int		offset_wdt;
	int		wdt;
	int		hgt;
	int		count;
	int		color;
	int		space;
	double	**mx;
	double	**my;
	double	**mz;
}			t_map;

typedef struct s_running
{
	t_map	*map;
	t_env	env;
}			t_running;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				ft_abs(int j);
int				ft_draw_map(t_running *run);
t_map			*ft_init_map(char *path);
void			ft_parse(int fd, char *path, char *line, t_map *map);
void			ft_draw_lines(t_running *run);
t_bresenham		*ft_init_bresenham(t_point *pix1, t_point *pix2);
void			ft_calculate_point(t_map *map, double **r, t_point **p);
t_point			**ft_init_coord(t_map *map);
double			**ft_alloc_matrix(void);
double			**ft_matrix_rx(double radian);
double			**ft_matrix_rz(double radian);
double			**ft_matrix_euler(t_map *map);
double			**ft_multiply_matrix(double **rx, double **rz);
double			ft_compute_size(t_map *map);
int				mouse_hook(int keycode, t_running *run);
void			ft_zoom(t_running *run, float coef);

#endif