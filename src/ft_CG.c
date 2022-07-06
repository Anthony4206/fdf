#include "fdf.h"

double	ft_length_vec3(t_point *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	ft_normalize(t_point *v)
{
	double	len;
	double	factor;

	len = v->x * v->x + v->y * v->y + v->z * v->z;
	if (len > 0)
	{
		factor = 1 / sqrt(len);
		//Récupérer nouvelle valeur dans une tmp ?
		v->x *= factor;
		v->y *= factor;
		v->z *= factor;
	}
}

double	ft_dot(t_point *a, t_point *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_point	ft_cross(t_point *a, t_point *b)
{
	t_point *ret;

	ret = malloc(sizeof(t_point));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->x = a->y * b->z - a->z * b->y;
	ret->y = a->z * b->x - a->x * b->z;
	ret->z = a->x * b->y - a->y * b->x;
	return (*ret);
}

void	ft_calculate_point(t_map *map, t_point **s)
{
	int		i;
	int		j;
	double	m[4][4];
	double	a;
	double	b;
	double	c;
	double	w;

	m[0][0] = 0.707;
	m[0][1] = 0.707;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = -0.707;
	m[1][1] = 0.707;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	j = 0;
	while (j < map->hgt)
	{
		i = 0;
		while (i < map->wdt)
		{
//			ft_printf("%d | %d\n", j, i);
			a = s[j][i].x * m[0][0] + s[j][i].y * m[1][0] + s[j][i].z * m[2][0] + m[3][0];
			b = s[j][i].x * m[0][1] + s[j][i].y * m[1][1] + s[j][i].z * m[2][1] + m[3][1];
			c = s[j][i].x * m[0][2] + s[j][i].y * m[1][2] + s[j][i].z * m[2][2] + m[3][2];
			w = s[j][i].x * m[0][3] + s[j][i].y * m[1][3] + s[j][i].z * m[2][3] + m[3][3];
			map->rotate[j][i].x = a / w;
			map->rotate[j][i].y = b / w;
			map->rotate[j][i].z = c / w;
			map->rotate[j][i].color = 0x00FF0000;
//			printf("%d | %d | %d\n", map->rotate[j][i].x, map->rotate[j][i].y, map->rotate[j][i].z);
			i++;
		}
		j++;
	}
}
