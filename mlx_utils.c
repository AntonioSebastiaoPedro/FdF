/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:56:43 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 12:22:07 by ansebast         ###   ########.fr       */
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
	vars->iso_angle = 0.5236;
	vars->altitude = 1;
}

int	ft_close(t_vars *vars_mlx)
{
	ft_freematrix(vars_mlx->map, vars_mlx->height, vars_mlx->width);
	mlx_destroy_image(vars_mlx->mlx, vars_mlx->img.img);
	mlx_destroy_window(vars_mlx->mlx, vars_mlx->mlx_win);
	mlx_destroy_display(vars_mlx->mlx);
	free(vars_mlx->mlx);
	exit(0);
	return (0);
}
