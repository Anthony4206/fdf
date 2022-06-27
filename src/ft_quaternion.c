/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:28:53 by alevasse          #+#    #+#             */
/*   Updated: 2022/06/27 10:43:38 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quaternion	ft_quaternion(double yaw, double pitch, double roll)
{
	t_quaternion	q;

	q.cy = cos(yaw * 0.5);
	q.sy = sin(yaw * 0.5);
	q.cp = cos(pitch * 0.5);
	q.sp = sin(pitch * 0.5);
	q.cr = cos(roll * 0.5);
	q.sr = sin(roll * 0.5);
	q.w = q.cr * q.cp * q.cy + q.sr * q.sp * q.sy;
	q.x = q.sr * q.cp * q.cy - q.cr * q.sp * q.sy;
	q.y = q.cr * q.sp * q.cy + q.sr * q.cp * q.sy;
	q.z = q.cr * q.cp * q.sy - q.sr * q.sp * q.cy;
	return (q);
}
