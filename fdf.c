/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:58 by ansebast          #+#    #+#             */
/*   Updated: 2024/09/30 17:00:03 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_point	project_point(int x, int y, int z, int color, double scale,
		int x_offset, int y_offset)
{
	t_point	proj;
	double	angle;

	angle = 0.5236;
	x *= scale;
	y *= scale;
	z *= scale;
	proj.x = (x + y) * cos(angle) + x_offset;
	proj.y = (x - y) * sin(-angle) - z + y_offset;
	proj.z = z;
	proj.color = color;
	return (proj);
}

static void	freearray(char **array, int pos)
{
	while (pos > 0)
		free(array[--pos]);
	free(array);
}

int	**parse_line(char *line, int *width)
{
	char	**split;
	int		**row;
	int		i;

	split = ft_split(line, ' ');
	for (*width = 0; split[*width]; (*width)++)
		;
	row = malloc(sizeof(int *) * (*width));
	if (!row)
	{
		perror("Erro ao alocar memória para linha");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *width)
	{
		row[i] = malloc(sizeof(int) * 2);
		row[i][0] = atoi(split[i]);
		if (ft_strchr(split[i], ','))
			row[i][1] = strtol(ft_strchr(split[i], ',') + 1, NULL, 16);
		else
			row[i][1] = DEFAULT_COLOR;
		i++;
	}
	freearray(split, i);
	return (row);
}

void	count_lines_columns(const char *filename, int *rows, int *cols)
{
	FILE	*file;
	char	*line;
	size_t	len;
	ssize_t	read;
	char	*token;

	file = fopen(filename, "r");
	if (!file)
	{
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}
	line = NULL;
	len = 0;
	*rows = 0;
	*cols = 0;
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (*rows == 0)
		{
			token = strtok(line, " ");
			while (token)
			{
				(*cols)++;
				token = strtok(NULL, " ");
			}
		}
		(*rows)++;
	}
	free(line);
	fclose(file);
}

int	hex_to_int(const char *hex_str)
{
	return (int)strtol(hex_str, NULL, 16);
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

void	draw_map(t_data *img, int ***map, int height, int width, double scale,
		int x_offset, int y_offset)
{
	int		x;
	int		y;
	t_point	p0;
	t_point	p1;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (!map[y] || !map[y][x])
				continue ;
			p0 = project_point(x, y, map[y][x][0], map[y][x][1], scale,
					x_offset, y_offset);
			if (x < width - 1 && map[y][x + 1])
			{
				p1 = project_point(x + 1, y, map[y][x + 1][0], map[y][x + 1][1],
						scale, x_offset, y_offset);
				draw_line(img, p0.x, p0.y, p1.x, p1.y, p0.color);
			}
			if (y < height - 1 && map[y + 1][x])
			{
				p1 = project_point(x, y + 1, map[y + 1][x][0], map[y + 1][x][1],
						scale, x_offset, y_offset);
				draw_line(img, p0.x, p0.y, p1.x, p1.y, p0.color);
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
int	ft_hand_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307 || keycode == 113)
		ft_close(vars);
        if (keycode == 65362)
        {
                
        }
	printf("%d\n", keycode);
	return (0);
}

t_bounds	get_projected_bounds(int ***map, int height, int width,
		double scale, int x_offset, int y_offset)
{
	t_bounds	bounds;
	t_point		p;
	int			first;

	int x, y;
	first = 1;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (!map[y] || !map[y][x])
				continue ;
			p = project_point(x, y, map[y][x][0], map[y][x][1], scale, x_offset,
					y_offset);
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


void	calculate_scale(int ****map, int *height, int *width, double *scale,
		int *x_offset, int *y_offset)
{
	t_bounds	bounds;
	double		scale_x;
	double		scale_y;

	bounds = get_projected_bounds(*map, *height, *width, *scale, *x_offset,
			*y_offset);
	scale_x = (double)WIN_WIDTH / ((bounds.max_x ) - (bounds.min_x ));
	scale_y = (double)(WIN_HEIGHT - 220) / (bounds.max_y - bounds.min_y);
	*scale = fmin(scale_x, scale_y);
	bounds = get_projected_bounds(*map, *height, *width, *scale, *x_offset,
			*y_offset);
	*x_offset = (WIN_WIDTH - (bounds.max_x - bounds.min_x)) / 2 - bounds.min_x;
	*y_offset = (WIN_HEIGHT - (bounds.max_y - bounds.min_y)) / 2 - bounds.min_y;
}

int	main(int ac, char **av)
{
	int		***map;
	int		height;
	int		width;
	t_vars	vars;

	if (ac != 2)
	{
		printf("Usage: %s <file.fdf>\n", av[0]);
		return (1);
	}
	map = read_map(av[1], &height, &width);
	if (!map)
	{
		printf("Error reading file.\n");
		return (1);
	}
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Ansebast's FdF");
	vars.img.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	vars.scale = 1.0;
	vars.x_offset = 0;
	vars.y_offset = 0;
	calculate_scale(&map, &height, &width, &vars.scale, &vars.x_offset, &vars.y_offset);
	draw_map(&vars.img, map, height, width, vars.scale, vars.x_offset, vars.y_offset);
	free_map(map, height, width);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 1L << 0, ft_hand_hook, &vars);
	mlx_hook(vars.mlx_win, 17, 1L << 0, ft_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
