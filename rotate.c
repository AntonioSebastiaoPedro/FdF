/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:44:00 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/02 13:25:02 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_point *points, t_vars *vars, t_point *proj)
{
	double	angle_z;
	double	iso_angle;
	double	x_rotate;
	double	y_rotate;

	angle_z = vars->angle_z;
	points->x -= vars->mid_width;
	points->x *= vars->scale;
	points->y -= vars->mid_height;
	points->y *= vars->scale;
	points->z *= vars->scale;
	x_rotate = points->x * cos(angle_z) - points->y * sin(angle_z);
	y_rotate = points->x * sin(angle_z) + points->y * cos(angle_z);
	iso_angle = 0.5236;
	proj->x = (x_rotate + y_rotate) * cos(iso_angle) + vars->x_offset;
	proj->y = (x_rotate - y_rotate) * -sin(iso_angle) - points->z + vars->y_offset;
}

void	rotate_y(t_point *points, t_vars *vars, t_point *proj)
{
	double	angle_y;
	double	iso_angle;
	double	x_rotate;
	double	z_rotate;


	angle_y = vars->angle_y;
	points->x -= vars->mid_width;
	points->x *= vars->scale;
	points->y -= vars->mid_height;
	points->y *= vars->scale;
	points->z *= vars->scale;
	x_rotate = points->x * cos(angle_y) + points->z * sin(angle_y);
	z_rotate = -points->x * sin(angle_y) + points->z * cos(angle_y);
	iso_angle = 0.5236;
	proj->x = (x_rotate - points->y) * cos(iso_angle) + vars->x_offset;
	proj->y = (x_rotate + points->y) * sin(iso_angle) - (z_rotate * vars->altitude) + vars->y_offset;
}

void	rotate_x(t_point *points, t_vars *vars, t_point *proj)
{
	double angle_x;
	double iso_angle;
	double y_rotate;
	double z_rotate;

	angle_x = vars->angle_x;
	points->x -= vars->mid_width;
	points->x *= vars->scale;
	points->y -= vars->mid_height;
	points->y *= vars->scale;
	points->z *= vars->scale;
	y_rotate = points->y * cos(angle_x) - points->z * sin(angle_x);
	z_rotate = points->y * sin(angle_x) + points->z * cos(angle_x);
	iso_angle = 0.5236;
	proj->x = (points->x - y_rotate) * cos(iso_angle) + vars->x_offset;
	proj->y = (points->x + y_rotate) * sin(iso_angle) - (z_rotate * vars->altitude) + vars->y_offset;
}


void    ft_realloc(void *oldptr, size_t oldsize, size_t newsize)
{
    void *newptr;

    newptr = malloc(newsize);
    if (!newptr)
    {
        free(oldptr);
        return ;
    }
    ft_memcpy(newptr, oldptr, oldsize);
    free(oldptr);
    oldptr = newptr;
}