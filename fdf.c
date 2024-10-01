/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:58 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 17:52:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>

// #define LOW_COLOR 0x0000FF
// #define HIGH_COLOR 0x006400
#define LOW_COLOR 0xFFFFFFFF
#define HIGH_COLOR 0xFFFFFFFF
#ifndef DEFAULT_COLOR
# define DEFAULT_COLOR 0xFFFFFF
#endif

int	**parse_line(char *line, int *width)
{
	char	**split;
	int		**row;
	int		i;

	split = ft_split(line, ' ');
	*width = 0;
	while (split[*width])
		(*width)++;
	row = malloc(sizeof(int *) * (*width));
	if (!row)
		ft_puterror("Error allocating memory for line\n", 1);
	i = 0;
	while (i < *width)
	{
		row[i] = malloc(sizeof(int) * 2);
		row[i][0] = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			row[i][1] = ft_strtol(ft_strchr(split[i], ',') + 1, NULL, 16);
		else
			row[i][1] = DEFAULT_COLOR;
		i++;
	}
	ft_freearray(split, i);
	return (row);
}

void	count_lines_columns(const char *filename, int *rows, int *cols)
{
	int		fd;
	char	*line;
	char	*token;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_puterror("Error opening file\n", 1);
	line = NULL;
	*rows = 0;
	*cols = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*rows == 0)
		{
			token = ft_strtok(line, " ");
			while (token)
			{
				(*cols)++;
				token = ft_strtok(NULL, " ");
			}
		}
		(*rows)++;
		free(line);
	}
	close(fd);
}

int	***read_map(const char *file, int *height, int *width)
{
	int		fd;
	int		i;
	char	*line;
	int		***map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	*height = 0;
	while ((line = get_next_line(fd)))
	{
		free(line);
		(*height)++;
	}
	close(fd);
	map = malloc(sizeof(int **) * (*height));
	fd = open(file, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map[i++] = parse_line(line, width);
		free(line);
	}
	close(fd);
	return (map);
}

void	free_map(int ***map, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			free(map[i][j]);
		}
		free(map[i]);
	}
	free(map);
}

int	interpolate_color(int cor_inicial, int cor_final, double t)
{
	int	r_inicial;
	int	g_inicial;
	int	b_inicial;
	int	r_final;
	int	g_final;
	int	b_final;
	int	r;
	int	g;
	int	b;

	r_inicial = (cor_inicial >> 16) & 0xFF;
	g_inicial = (cor_inicial >> 8) & 0xFF;
	b_inicial = cor_inicial & 0xFF;
	r_final = (cor_final >> 16) & 0xFF;
	g_final = (cor_final >> 8) & 0xFF;
	b_final = cor_final & 0xFF;
	r = (int)((1 - t) * r_inicial + t * r_final);
	g = (int)((1 - t) * g_inicial + t * g_final);
	b = (int)((1 - t) * b_inicial + t * b_final);
	return ((r << 16) | (g << 8) | b);
}

int	get_color_from_altitude(int z, int z_min, int z_max)
{
	double	ratio;

	if (z_max == z_min)
		ratio = 1.0;
	else
		ratio = (double)(z - z_min) / (z_max - z_min);
	return (interpolate_color(LOW_COLOR, HIGH_COLOR, ratio));
}

void	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_map(t_vars *vars)
{
	int		x;
	int		y;
	t_point	p0;
	t_point	p1;

	for (y = 0; y < vars->height; y++)
	{
		for (x = 0; x < vars->width; x++)
		{
			if (!vars->map[y] || !vars->map[y][x])
				continue ;
			vars->map[y][x][1] = get_color_from_altitude(vars->map[y][x][0],
					vars->z_min, vars->z_max);
			p0 = project_point(x, y, vars->map[y][x][0], vars->map[y][x][1],
					vars);
			if (x < vars->width - 1 && vars->map[y][x + 1])
			{
				p1 = project_point(x + 1, y, vars->map[y][x + 1][0],
						vars->map[y][x + 1][1], vars);
				draw_line(&vars->img, p0.x, p0.y, p1.x, p1.y, p0.color);
			}
			if (y < vars->height - 1 && vars->map[y + 1][x])
			{
				p1 = project_point(x, y + 1, vars->map[y + 1][x][0], vars->map[y
						+ 1][x][1], vars);
				draw_line(&vars->img, p0.x, p0.y, p1.x, p1.y, p0.color);
			}
		}
	}
}

int	ft_close(t_vars *vars_mlx)
{
	mlx_destroy_image(vars_mlx->mlx, vars_mlx->img.img);
	mlx_destroy_window(vars_mlx->mlx, vars_mlx->mlx_win);
	mlx_destroy_display(vars_mlx->mlx);
	free(vars_mlx->mlx);
	exit(0);
	return (0);
}

void	update_map(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
}

int	zoom(int keycode, int x, int y, t_vars *vars)
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

int	ft_hand_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		ft_close(vars);
	if (keycode == ' ' || keycode == 65288)
	{
                if (keycode == ' ')
		        vars->angle_z += 0.1;
                else
		        vars->angle_z -= 0.1;
		vars->rotate = 1;
		update_map(vars);
	}
	if (keycode == 'z' || keycode == 'x')
	{
                if (keycode == 'z')
		        vars->altitude += 0.1;
                else
		        vars->altitude -= 0.1;
		update_map(vars);
	}
	if (keycode == 'i' || keycode == 'o')
	{
		if (keycode == 'i')
		        vars->altitude += 0.1;
                else
		        vars->altitude -= 0.1;
                vars->rotate = 2;
		update_map(vars);
	}
	if (keycode == 'k' || keycode == 'l')
	{
		if (keycode == 'k')
		        vars->angle_y += 0.1;
                else
		        vars->angle_y -= 0.1;
                vars->rotate = 3;
		update_map(vars);
	}
	if (keycode == 61 || keycode == 45)
		zoom(keycode, 0, 0, vars);
	if (keycode >= 65361 && keycode <= 65364)
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
	printf("%d\n", keycode);
	return (0);
}

t_bounds	get_projected_bounds(t_vars *vars)
{
	t_bounds	bounds;
	t_point		p;
	int			first;

	int x, y;
	first = 1;
	for (y = 0; y < vars->height; y++)
	{
		for (x = 0; x < vars->width; x++)
		{
			if (!vars->map[y] || !vars->map[y][x])
				continue ;
			p = project_point(x, y, vars->map[y][x][0], vars->map[y][x][1],
					vars);
			if (first)
			{
				bounds.min_x = bounds.max_x = p.x;
				bounds.min_y = bounds.max_y = p.y;
				first = 0;
			}
			else
			{
				if (p.x < bounds.min_x)
					bounds.min_x = p.x;
				if (p.x > bounds.max_x)
					bounds.max_x = p.x;
				if (p.y < bounds.min_y)
					bounds.min_y = p.y;
				if (p.y > bounds.max_y)
					bounds.max_y = p.y;
			}
		}
	}
	return (bounds);
}

void	calculate_scale(t_vars *vars)
{
	t_bounds	bounds;
	double		scale_x;
	double		scale_y;

	bounds = get_projected_bounds(vars);
	scale_x = (double)WIN_WIDTH / ((bounds.max_x) - (bounds.min_x));
	scale_y = (double)(WIN_HEIGHT - 200) / (bounds.max_y - bounds.min_y);
	vars->scale = fmin(scale_x, scale_y);
	bounds = get_projected_bounds(vars);
	vars->x_offset = (WIN_WIDTH - (bounds.max_x - bounds.min_x)) / 2
		- bounds.min_x;
	vars->y_offset = (WIN_HEIGHT - (bounds.max_y - bounds.min_y)) / 2
		- bounds.min_y;
}

void	get_min_max_z(t_vars *vars)
{
	int	z_atual;

	for (int i = 0; i < vars->height; i++)
	{
		for (int j = 0; j < vars->width; j++)
		{
			z_atual = vars->map[i][j][0];
			if (z_atual < vars->z_min)
				vars->z_min = z_atual;
			if (z_atual > vars->z_max)
				vars->z_max = z_atual;
		}
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		ft_puterror("Usage: ./fdf <file.fdf>\n", 1);
	vars.map = read_map(av[1], &vars.height, &vars.width);
	if (!vars.map)
		ft_puterror("Usage: ./fdf <file.fdf>\n", 1);
	init_vars(&vars);
	get_min_max_z(&vars);
	calculate_scale(&vars);
	draw_map(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 1L << 0, ft_hand_hook, &vars);
	mlx_mouse_hook(vars.mlx_win, zoom, &vars);
	mlx_hook(vars.mlx_win, 17, 1L << 0, ft_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
