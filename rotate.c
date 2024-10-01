/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:44:00 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 17:19:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(int x, int y, int z, t_vars *vars, t_point *proj)
{
	double	angle_z;
	double	iso_angle;
	double	x_rotate;
	double	y_rotate;

	angle_z = vars->angle_z;
	x -= vars->mid_width;
	x *= vars->scale;
	y -= vars->mid_height;
	y *= vars->scale;
	z *= vars->scale;
	x_rotate = x * cos(angle_z) - y * sin(angle_z);
	y_rotate = x * sin(angle_z) + y * cos(angle_z);
	iso_angle = 0.5236;
	proj->x = (x_rotate + y_rotate) * cos(iso_angle) + vars->x_offset;
	proj->y = (x_rotate - y_rotate) * -sin(iso_angle) - z + vars->y_offset;
}

void	rotate_y(int x, int y, int z, t_vars *vars, t_point *proj)
{
	double	angle_y;
	double	iso_angle;
	double	x_rotate;
	double	z_rotate;

	angle_y = vars->angle_y;
	x -= vars->mid_width;
	x *= vars->scale;
	y -= vars->mid_height;
	y *= vars->scale;
	z *= vars->scale;
	x_rotate = x * cos(angle_y) + z * sin(angle_y);
	z_rotate = -x * sin(angle_y) + z * cos(angle_y);
	iso_angle = 0.5236;
	proj->x = (x_rotate - y) * cos(iso_angle) + vars->x_offset;
	proj->y = (x_rotate + y) * sin(iso_angle) - (z_rotate * vars->altitude) + vars->y_offset;
}

void	rotate_x(int x, int y, int z, t_vars *vars, t_point *proj)
{
	double angle_x;
	double iso_angle;
	double y_rotate;
	double z_rotate;

	angle_x = vars->angle_x;
	x -= vars->mid_width;
	x *= vars->scale;
	y -= vars->mid_height;
	y *= vars->scale;
	z *= vars->scale;
	y_rotate = y * cos(angle_x) - z * sin(angle_x);
	z_rotate = y * sin(angle_x) + z * cos(angle_x);
	iso_angle = 0.5236;
	proj->x = (x - y_rotate) * cos(iso_angle) + vars->x_offset;
	proj->y = (x + y_rotate) * sin(iso_angle) - (z_rotate * vars->altitude) + vars->y_offset;
}