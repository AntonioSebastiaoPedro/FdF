/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:58 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/05 10:58:59 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	calculate_scale(&vars);
	draw_map(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 1L << 0, ft_hand_hook, &vars);
	mlx_hook(vars.mlx_win, 17, 1L << 0, ft_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
