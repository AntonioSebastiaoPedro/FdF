/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:55 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 06:53:59 by ansebast         ###   ########.fr       */
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
	double	scale;
	double	altitude;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	int		x_offset;
	int		y_offset;
	int		***map;
	int		height;
	int		width;
	int		z_min;
	int		z_max;
	int		mid_width;
	int		mid_height;
	int		rotate;
	t_data	img;
}			t_vars;

typedef struct
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
}			t_bounds;
typedef struct s_bresenham
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_bresenham;

typedef struct s_data_rotate
{
	double	angle_x;
	double	angle_y;
	double	angle_z;
	double	x_rotate;
	double	y_rotate;
	double	z_rotate;
	double	iso_angle;
}			t_data_rotate;

typedef struct s_colors
{
	int		r_initial;
	int		g_initial;
	int		b_initial;
	int		r_final;
	int		g_final;
	int		b_final;
}			t_colors;

t_point		project_point(t_point *points, t_vars *vars);
t_bounds	get_projected_bounds(t_vars *vars);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		init_vars(t_vars *vars);
void		rotate_x(t_point *points, t_vars *vars, t_point *proj);
void		rotate_y(t_point *points, t_vars *vars, t_point *proj);
void		rotate_z(t_point *points, t_vars *vars, t_point *proj);
void		get_min_max_z(t_vars *vars);
void		ft_freematrix(int ***map, int rows, int cols);
void		draw_map(t_vars *vars);
void		update_map(t_vars *vars);
void		calculate_scale(t_vars *vars);
void		draw_line(t_data *img, t_point p0, t_point p1);
void		draw_horizontal_lines(t_vars *vars, t_point *new_point, t_point *p0,
				t_point *p1);
void		draw_vertical_lines(t_vars *vars, t_point *new_point, t_point *p0,
				t_point *p1);
int			ft_close(t_vars *vars_mlx);
int			ft_hand_hook(int keycode, t_vars *vars);
int			zoom_object(int keycode, int x, int y, t_vars *vars);
int			***read_map(const char *file, int *height, int *width);
int			**parse_line(char *line, int *width);
int			interpolate_color(int cor_initial, int cor_final, double t);
int			get_color_from_altitude(int z, int z_min, int z_max);

#endif