/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:55 by ansebast          #+#    #+#             */
/*   Updated: 2024/09/28 10:12:47 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef DEFAULT_COLOR
#  define DEFAULT_COLOR 0xFFFFFF
# endif

// Definições de tamanho da janela
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Teclas de controle
# define KEY_UP 126
# define KEY_DOWN 125
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
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

#endif