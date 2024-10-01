/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:03:36 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 19:26:17 by ansebast         ###   ########.fr       */
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

void	update_bounds(int *first, t_bounds *bounds, t_point *point)
{
	if (*first)
	{
		bounds->min_x = bounds->max_x = point->x;
		bounds->min_y = bounds->max_y = point->y;
		*first = 0;
	}
	else
	{
		if (point->x < bounds->min_x)
			bounds->min_x = point->x;
		if (point->x > bounds->max_x)
			bounds->max_x = point->x;
		if (point->y < bounds->min_y)
			bounds->min_y = point->y;
		if (point->y > bounds->max_y)
			bounds->max_y = point->y;
	}
}

t_bounds	get_projected_bounds(t_vars *vars)
{
	t_bounds	bounds;
	t_point		p;
	int			first;
	int			x;
	int			y;

	first = 1;
	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			if (!vars->map[y] || !vars->map[y][x])
				continue ;
			p = project_point(x, y, vars->map[y][x][0], vars->map[y][x][1],
					vars);
			update_bounds(&first, &bounds, &p);
			x++;
		}
		y++;
	}
	return (bounds);
}
