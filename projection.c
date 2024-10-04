/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:03:36 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/04 20:40:35 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_point(t_point *points, t_vars *vars)
{
	t_point	proj;

	rotate(points, vars, &proj);
	return (proj);
}

void	update_bounds(int *first, t_bounds *bounds, t_point *point)
{
	if (*first)
	{
		bounds->min_x = point->x;
		bounds->max_x = point->x;
		bounds->min_y = point->y;
		bounds->max_y = point->y;
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
	t_point		new_point;

	first = 1;
	new_point.y = 0;
	while (new_point.y < vars->height)
	{
		new_point.x = 0;
		while (new_point.x < vars->width)
		{
			if (vars->map[new_point.y] && vars->map[new_point.y][new_point.x])
			{
				new_point.color = vars->map[new_point.y][new_point.x][1];
				new_point.z = vars->map[new_point.y][new_point.x][0];
				p = project_point(&new_point, vars);
				update_bounds(&first, &bounds, &p);
			}
			new_point.x++;
		}
		new_point.y++;
	}
	return (bounds);
}
