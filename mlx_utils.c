/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:56:43 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 17:19:18 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void	init_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT,
			"Ansebast's FdF");
	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	vars->mid_height = vars->height / 2;
	vars->mid_width = vars->width / 4;
	vars->scale = 1.0;
	vars->x_offset = 0;
	vars->y_offset = 0;
	vars->z_min = INT_MAX;
	vars->z_max = INT_MIN;
	vars->rotate = 1;
	vars->angle_z = 0.5236;
        vars->altitude = 1;
}