/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:44:00 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 12:21:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate(t_point *points, t_vars *vars, t_point *proj)
{
	t_data_rotate	data_rotate;
	double			tmp_x;
	double			tmp_y;
	double			tmp_z;

	data_rotate.x = points->x - vars->mid_width;
	data_rotate.y = points->y - vars->mid_height;
	data_rotate.z = points->z;
	data_rotate.x *= vars->scale;
	data_rotate.y *= vars->scale;
	data_rotate.z *= vars->scale;
	rotate_x(&tmp_y, &tmp_z, &data_rotate, vars);
	rotate_y(&tmp_x, &tmp_z, &data_rotate, vars);
	rotate_z(&tmp_x, &tmp_y, &data_rotate, vars);
	proj->x = (data_rotate.x - data_rotate.y) * cos(vars->iso_angle)
		+ vars->x_offset;
	proj->y = (data_rotate.x + data_rotate.y) * sin(vars->iso_angle)
		- data_rotate.z + vars->y_offset;
}

void	rotate_x(double *y, double *z, t_data_rotate *data_rotate, t_vars *vars)
{
	*y = data_rotate->y * cos(vars->angle_x) - data_rotate->z
		* sin(vars->angle_x);
	*z = data_rotate->y * sin(vars->angle_x) + data_rotate->z
		* cos(vars->angle_x);
	data_rotate->y = *y;
	data_rotate->z = *z;
}

void	rotate_y(double *x, double *z, t_data_rotate *data_rotate, t_vars *vars)
{
	*x = data_rotate->x * cos(vars->angle_y) + data_rotate->z
		* sin(vars->angle_y);
	*z = -data_rotate->x * sin(vars->angle_y) + data_rotate->z
		* cos(vars->angle_y);
	data_rotate->x = *x;
	data_rotate->z = *z;
}

void	rotate_z(double *x, double *y, t_data_rotate *data_rotate, t_vars *vars)
{
	*x = data_rotate->x * cos(vars->angle_z) - data_rotate->y
		* sin(vars->angle_z);
	*y = data_rotate->x * sin(vars->angle_z) + data_rotate->y
		* cos(vars->angle_z);
	data_rotate->x = *x;
	data_rotate->y = *y;
}
