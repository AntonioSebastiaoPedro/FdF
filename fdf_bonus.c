/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:58 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/05 15:10:39 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	put_instructions(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 20, 0x00FF00, "Instructions:");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 40, 0xFFFFFF,
		"Press ESC or click on the cross on the window's frame to exit");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 60, 0xFFFFFF,
		"Press I or O to rotate on the X-axis:");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 80, 0xFFFFFF,
		"Press K or L to rotate on the Y-axis:");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 100, 0xFFFFFF,
		"Press Space or Backspace to rotate on the Z-axis:");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 120, 0xFFFFFF,
		"Press Z or X to increase or decrease the altitude of the object:");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 140, 0xFFFFFF,
		"Press the arrows to move the object");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 160, 0xFFFFFF,
		"Press + or - to zoom in or zoom out");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 180, 0xFFFFFF,
		"You can also use the mouse scroll wheel to zoom in or out");
	mlx_string_put(vars->mlx, vars->mlx_win, 20, 200, 0xFFFFFF,
		"Press A to apply a custom color:");
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		ft_puterror("Usage: ./fdf <file.fdf>\n", 1);
	check_file(av[1]);
	vars.map = read_map(av[1], &vars.height, &vars.width);
	if (!vars.map)
		ft_puterror("Invalid File\n", 1);
	init_vars(&vars);
	get_min_max_z(&vars);
	calculate_scale(&vars);
	draw_map(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	put_instructions(&vars);
	mlx_hook(vars.mlx_win, 2, 1L << 0, ft_hand_hook, &vars);
	mlx_mouse_hook(vars.mlx_win, zoom_object, &vars);
	mlx_hook(vars.mlx_win, 17, 1L << 0, ft_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
