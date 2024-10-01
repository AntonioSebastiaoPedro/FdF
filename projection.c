/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:03:36 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 18:06:18 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_point(int x, int y, int z, int color, t_vars *vars)
{
	t_point	proj;
	if (vars->rotate == 1)
                rotate_z(x, y, z, vars, &proj);
        else if (vars->rotate == 2)
                rotate_x(x, y, z, vars, &proj);
        else if (vars->rotate == 3)
                rotate_y(x, y, z, vars, &proj);
	proj.z = z;
	proj.color = color;
	return (proj);
}

t_bounds	get_projected_bounds(t_vars *vars)
{
	t_bounds	bounds;
	t_point		p;
	int			first;

	int x, y;
	first = 1;
	for (y = 0; y < vars->height; y++)
	{
		for (x = 0; x < vars->width; x++)
		{
			if (!vars->map[y] || !vars->map[y][x])
				continue ;
			p = project_point(x, y, vars->map[y][x][0], vars->map[y][x][1],
					vars);
			if (first)
			{
				bounds.min_x = bounds.max_x = p.x;
				bounds.min_y = bounds.max_y = p.y;
				first = 0;
			}
			else
			{
				if (p.x < bounds.min_x)
					bounds.min_x = p.x;
				if (p.x > bounds.max_x)
					bounds.max_x = p.x;
				if (p.y < bounds.min_y)
					bounds.min_y = p.y;
				if (p.y > bounds.max_y)
					bounds.max_y = p.y;
			}
		}
	}
	return (bounds);
}