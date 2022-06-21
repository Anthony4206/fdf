/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/09 13:54:25 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

int	rgb_to_int(double r, double g, double b)
{
	int	color;

	color = 0;
	color |= (int)(b * 255);
	color |= (int)(g * 255) << 8;
	color |= (int)(r * 255) << 16;
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	e;

	e = x2 - x1;
	dx = e * 2;
	dy = (y2 - y1) * 2;
	while (x1 < x2)
	{
		my_mlx_pixel_put(img, x1, y1, color);
		x1 += 1;
		if (e - dy <= 0)
		{
			y1 += 1;
			e = e + dx;
		}
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
//	t_point	point;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 50, 50, 0xFF000000);
	//draw_line(img.img, 10, 10, 60, 60, );
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

/*void	draw_line(t_data *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	e;

	e = x2 - x1;
	dx = e * 2;
	dy = (y2 - y1) * 2;
	float a = (float) dy / (float) dx;
	int b = a * x1 - y1;
	while (x1 < x2)
	{
		my_mlx_pixel_put(img, x1, (int) (a * x1) + b, color);
		x1 += 1;
		if (e - dy <= 0)
		{
			y1 += 1;
			e = e + dx;
		}
	}
}*/

/*void	draw_line2(t_data *img, int *start, int *end, int color)
{
	int	dx;
	int	dy;
	int	e;

	e = end[0] - start[0];
	dx = e * 2;
	dy = (end[1] - start[1]) * 2;
	while (start[0] < end[0])
	{
		my_mlx_pixel_put(img, start[0], end[0], color);
		x1 += 1;
		if (e - dy <= 0)
		{
			y1 += 1;
			e = e + dx;
		}
	}
}*/
