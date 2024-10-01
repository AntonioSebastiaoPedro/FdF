/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:54:08 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 18:08:28 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min_max_z(t_vars *vars)
{
	int	z_atual;
        int i;
        int j;

        i = 0;
	while (i < vars->height)
	{
                j = 0;
		while (j < vars->width)
		{
			z_atual = vars->map[i][j][0];
			if (z_atual < vars->z_min)
				vars->z_min = z_atual;
			if (z_atual > vars->z_max)
				vars->z_max = z_atual;
                        j++;
		}
                i++;
	}
}

void	calculate_scale(t_vars *vars)
{
	t_bounds	bounds;
	double		scale_x;
	double		scale_y;

	bounds = get_projected_bounds(vars);
	scale_x = (double)WIN_WIDTH / ((bounds.max_x) - (bounds.min_x));
	scale_y = (double)(WIN_HEIGHT - 200) / (bounds.max_y - bounds.min_y);
	vars->scale = fmin(scale_x, scale_y);
	bounds = get_projected_bounds(vars);
	vars->x_offset = (WIN_WIDTH - (bounds.max_x - bounds.min_x)) / 2
		- bounds.min_x;
	vars->y_offset = (WIN_HEIGHT - (bounds.max_y - bounds.min_y)) / 2
		- bounds.min_y;
}