/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:54:08 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/05 20:13:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_scale(t_vars *vars)
{
	t_bounds	bounds;
	double		scale_x;
	double		scale_y;

	bounds = get_projected_bounds(vars);
	scale_x = (double)WIN_WIDTH / ((bounds.max_x) - (bounds.min_x));
	scale_y = (double)(WIN_HEIGHT - 220) / (bounds.max_y - bounds.min_y);
	vars->scale = fmin(scale_x, scale_y);
	if (vars->scale > 300)
		vars->scale = 300;
	bounds = get_projected_bounds(vars);
	vars->x_offset = (WIN_WIDTH - (bounds.max_x - bounds.min_x)) / 2
		- bounds.min_x;
	vars->y_offset = (WIN_HEIGHT - (bounds.max_y - bounds.min_y)) / 2
		- bounds.min_y;
}
