/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:44:00 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 06:58:05 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_point *points, t_vars *vars, t_point *proj)
{
	int				x;
	int				y;
	int				z;
	t_data_rotate	data_rotate;

	x = points->x;
	y = points->y;
	z = points->z;
	data_rotate.angle_z = vars->angle_z;
	x -= vars->mid_width;
	x *= vars->scale;
	y -= vars->mid_height;
	y *= vars->scale;
	z *= vars->scale;
	data_rotate.x_rotate = x * cos(data_rotate.angle_z) - y
		* sin(data_rotate.angle_z);
	data_rotate.y_rotate = x * sin(data_rotate.angle_z) + y
		* cos(data_rotate.angle_z);
	data_rotate.iso_angle = 0.5236;
	proj->x = (data_rotate.x_rotate + data_rotate.y_rotate)
		* cos(data_rotate.iso_angle) + vars->x_offset;
	proj->y = (data_rotate.x_rotate - data_rotate.y_rotate) *
		-sin(data_rotate.iso_angle) - z + vars->y_offset;
}

void	rotate_y(t_point *points, t_vars *vars, t_point *proj)
{
	int				x;
	int				y;
	int				z;
	t_data_rotate	data_rotate;

	x = points->x;
	y = points->y;
	z = points->z;
	data_rotate.angle_y = vars->angle_y;
	x -= vars->mid_width;
	x *= vars->scale;
	y -= vars->mid_height;
	y *= vars->scale;
	z *= vars->scale;
	data_rotate.x_rotate = x * cos(data_rotate.angle_y) + z
		* sin(data_rotate.angle_y);
	data_rotate.z_rotate = -x * sin(data_rotate.angle_y) + z
		* cos(data_rotate.angle_y);
	data_rotate.iso_angle = 0.5236;
	proj->x = (data_rotate.x_rotate - y) * cos(data_rotate.iso_angle)
		+ vars->x_offset;
	proj->y = (data_rotate.x_rotate + y) * sin(data_rotate.iso_angle)
		- (data_rotate.z_rotate * vars->altitude) + vars->y_offset;
}

void	rotate_x(t_point *points, t_vars *vars, t_point *proj)
{
	int				x;
	int				y;
	int				z;
	t_data_rotate data_rotate;

	x = points->x;
	y = points->y;
	z = points->z;
	data_rotate.angle_x = vars->angle_x;
	x -= vars->mid_width;
	x *= vars->scale;
	y -= vars->mid_height;
	y *= vars->scale;
	z *= vars->scale;
	data_rotate.y_rotate = y * cos(data_rotate.angle_x) - z
		* sin(data_rotate.angle_x);
	data_rotate.z_rotate = y * sin(data_rotate.angle_x) + z
		* cos(data_rotate.angle_x);
	data_rotate.iso_angle = 0.5236;
	proj->x = (x - data_rotate.y_rotate) * cos(data_rotate.iso_angle)
		+ vars->x_offset;
	proj->y = (x + data_rotate.y_rotate) * sin(data_rotate.iso_angle)
		- (data_rotate.z_rotate * vars->altitude) + vars->y_offset;
}