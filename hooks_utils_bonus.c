/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:11:06 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/05 08:33:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	transate_object(int keycode, t_vars *vars)
{
	if (keycode == 65361)
		vars->x_offset -= 10;
	else if (keycode == 65363)
		vars->x_offset += 10;
	else if (keycode == 65362)
		vars->y_offset -= 10;
	else if (keycode == 65364)
		vars->y_offset += 10;
	update_map(vars);
}

void	change_altitude_object(int keycode, t_vars *vars)
{
	if (keycode == 'z')
		vars->altitude += 0.1;
	else
		vars->altitude -= 0.1;
	update_map(vars);
}

int	zoom_object(int keycode, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if ((keycode == 5 || keycode == 45))
	{
		vars->scale *= 0.79;
		update_map(vars);
	}
	else if ((keycode == 4 || keycode == 61))
	{
		vars->scale *= 1.11;
		update_map(vars);
	}
	return (0);
}

void	rotate_object(int keycode, t_vars *vars)
{
	if (keycode == 'i' || keycode == 'o')
	{
		if (keycode == 'i')
			vars->angle_x += 0.1;
		else
			vars->angle_x -= 0.1;
		vars->rotate = 1;
	}
	if (keycode == 'k' || keycode == 'l')
	{
		if (keycode == 'k')
			vars->angle_y += 0.1;
		else
			vars->angle_y -= 0.1;
		vars->rotate = 1;
	}
	if (keycode == ' ' || keycode == 65288)
	{
		if (keycode == ' ')
			vars->angle_z += 0.1;
		else
			vars->angle_z -= 0.1;
		vars->rotate = 1;
	}
	update_map(vars);
}

int	ft_hand_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		ft_close(vars);
	if (keycode == 'z' || keycode == 'x')
		change_altitude_object(keycode, vars);
	if (keycode == ' ' || keycode == 65288 || keycode == 'i' || keycode == 'o'
		|| keycode == 'k' || keycode == 'l')
		rotate_object(keycode, vars);
	if (keycode == 61 || keycode == 45)
		zoom_object(keycode, 0, 0, vars);
	if (keycode == 'a')
	{
		vars->color = 1;
		update_map(vars);
	}
	if (keycode >= 65361 && keycode <= 65364)
		transate_object(keycode, vars);
	return (0);
}
