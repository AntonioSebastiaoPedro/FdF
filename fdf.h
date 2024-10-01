/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:55 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 08:47:42 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080


# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	double	scale;
	int		x_offset;
	int		y_offset;
	int		***map;
	int		height;
	int		width;
        int		z_min;
	int		z_max;
}			t_vars;

typedef struct
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
}			t_bounds;

#endif