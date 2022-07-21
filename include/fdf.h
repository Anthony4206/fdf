/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:45 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 22:58:03 by Anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define WIN_WDT 900
# define WIN_HGT 600

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
}		t_brez;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}			t_pt;

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

typedef struct s_geo
{
	t_pt	**vo;
	t_pt	**v;
	t_pt	**rotate;
	t_pt	**save;
	double	**mx;
	double	**my;
	double	**mz;
	double	**ri;
	double	**r;
}			t_geo;

typedef struct s_map
{
	int		x_origin;
	int		y_origin;
	int		min_z;
	int		max_z;
	int		alt;
	int		wdt;
	int		hgt;
	int		count;
	int		space;
	int		cone;
	t_geo	*geo;
}			t_map;

typedef struct s_running
{
	t_map	*map;
	t_env	env;
}			t_run;

// bresenham
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_fst_condition(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_snd_condition(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_diagonal(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_exeption(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
// calculate_utils
int		ft_abs(int j);
int		ft_middle(t_map *map, t_geo *geo, int opts);
//	close
int		ft_close(t_env *env);
// color utils
int		ft_create_trgb(int t, int r, int g, int b);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		degrad(int c1, int c2, float pct);
// color
int		ft_add_color(t_map *map, double z);
int		ft_put_color(t_pt *pix1, t_pt *pix2, float pct);
// draw_map
void	ft_push_line(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_calculate_point(t_map *map, double **r, t_pt **v, t_pt **vo);
void	ft_draw_lines(t_run *run, t_map *map, t_geo *geo);
int		ft_draw_map(t_run *run);
//hook
void	ft_perspective(t_pt **v, int p, int i, int j);
void	ft_zoom(t_map *map, t_geo *geo, float coef);
void	ft_rotation(int keycode, t_geo *geo);
int		key_hook(int keycode, t_run *run);
// htoi
int		ft_htoi(const char *str);
// init
t_brez	*ft_init_brez(t_pt *pix1, t_pt *pix2);
void	ft_init_color(t_map *map, t_geo *geo);
t_geo	*ft_init_geo(t_map *map);
void	ft_init_size(int fd, char *line, t_map *map);
t_map	*ft_init_map(char *path);
// matrix
double	**ft_alloc_matrix(void);
double	**ft_matrix_rx(double radian);
double	**ft_matrix_ry(double radian);
double	**ft_matrix_rz(double radian);
double	**ft_multiply_matrix(double **rx, double **rz);
// parse_utils
t_pt	**ft_alloc_coord(t_map *map);
int		ft_count_wdt(char *line);
int		ft_count_hgt(int fd, char *line);
void	ft_next_atoi(char *line, int *k);
double	ft_compute_size(t_map *map);
// parse
int		ft_altitude(t_map *map, t_geo *geo);
void	ft_add_z(t_map *map, t_geo *geo);
void	ft_add_coord(char *line, t_map *map, t_geo *geo, int j);
void	ft_parse(int fd, char *path, char *line, t_map *map);

#endif
