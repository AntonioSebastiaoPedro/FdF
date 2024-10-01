/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:58:19 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 19:16:13 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define LOW_COLOR 0xFFFFFFFF
#define HIGH_COLOR 0xFFFFFFFF

int	interpolate_color(int cor_inicial, int cor_final, double t)
{
	t_colors	colors;
	int			r;
	int			g;
	int			b;

	colors.r_inicial = (cor_inicial >> 16) & 0xFF;
	colors.g_inicial = (cor_inicial >> 8) & 0xFF;
	colors.b_inicial = cor_inicial & 0xFF;
	colors.r_final = (cor_final >> 16) & 0xFF;
	colors.g_final = (cor_final >> 8) & 0xFF;
	colors.b_final = cor_final & 0xFF;
	r = (int)((1 - t) * colors.r_inicial + t * colors.r_final);
	g = (int)((1 - t) * colors.g_inicial + t * colors.g_final);
	b = (int)((1 - t) * colors.b_inicial + t * colors.b_final);
	return ((r << 16) | (g << 8) | b);
}

int	get_color_from_altitude(int z, int z_min, int z_max)
{
	double ratio;

	if (z_max == z_min)
		ratio = 1.0;
	else
		ratio = (double)(z - z_min) / (z_max - z_min);
	return (interpolate_color(LOW_COLOR, HIGH_COLOR, ratio));
}