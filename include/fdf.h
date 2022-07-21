/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anthony <Anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 07:39:45 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/21 16:15:31 by Anthony          ###   ########.fr       */
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

/*typedef struct s_math
{
}*/

typedef struct s_map
{
	t_pt	**vo;
	t_pt	**v;
	t_pt	**rotate;
	double	**ri;
	double	**r;
	t_pt	**save;
	int		x_origin;
	int		y_origin;
	int		min_z;
	int		max_z;
	int		alt;
	int		offset_hgt;
	int		offset_wdt;
	int		wdt;
	int		hgt;
	int		count;
	int		color;
	int		space;
	int		cone;
	double	**mx;
	double	**my;
	double	**mz;
}			t_map;

typedef struct s_running
{
	t_map	*map;
	t_env	env;
}			t_run;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_abs(int j);
int		ft_draw_map(t_run *run);
t_map	*ft_init_map(char *path);
void	ft_parse(int fd, char *path, char *line, t_map *map);
void	ft_draw_lines(t_run *run);
t_brez	*ft_init_brez(t_pt *pix1, t_pt *pix2);
void	ft_calculate_point(t_map *map, double **r, t_pt **p);
void	ft_add_coord(char *line, t_map *map, int j);
double	**ft_alloc_matrix(void);
double	**ft_matrix_rx(double radian);
double	**ft_matrix_ry(double radian);
double	**ft_matrix_rz(double radian);
double	**ft_multiply_matrix(double **rx, double **rz);
double	ft_compute_size(t_map *map);
int		ft_htoi(const char *str);
void	ft_zoom(t_run *run, float coef);
int		ft_middle(t_map *map, int opts);
void	ft_add_z(t_map *map);
int		ft_altitude(t_map *map);
void	ft_init_color(t_map *map);
int		ft_add_color(t_map *map, double z);
int		ft_put_color(t_pt *pix1, t_pt *pix2, float pct);
void	ft_change_coord(t_map *map);
int		key_hook(int keycode, t_run *run);
int		ft_close(t_env *env);
void	ft_next_atoi(char *line, int *k);
int		ft_count_wdt(char *line);
int		ft_count_hgt(int fd, char *line);
t_pt	**ft_alloc_coord(t_map *map);
void	ft_rotation(int keycode, t_run *run);

// color
int		ft_put_color(t_pt *pix1, t_pt *pix2, float pct);
// bresenham
void	ft_fst_condition(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_snd_condition(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_diagonal(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
void	ft_exeption(t_run *run, t_pt *pix1, t_pt *pix2, t_brez *line);
// color utils
int		ft_create_trgb(int t, int r, int g, int b);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		degrad(int c1, int c2, float pct);

#endif
