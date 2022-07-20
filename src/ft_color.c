/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 06:33:57 by alevasse          #+#    #+#             */
/*   Updated: 2022/07/20 12:23:14 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_put_color(t_point *pix1, t_point *pix2, float pct)
{
	return (ft_create_trgb(0,
			degrad(get_r(pix1->color), get_r(pix2->color), pct),
			degrad(get_g(pix1->color), get_g(pix2->color), pct),
			degrad(get_b(pix1->color), get_b(pix2->color), pct)));
}
