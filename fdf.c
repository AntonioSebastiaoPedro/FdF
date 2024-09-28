/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:58 by ansebast          #+#    #+#             */
/*   Updated: 2024/09/28 10:57:24 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return;
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_point	project_point(int x, int y, int z, int color, double scale, int x_offset,
		int y_offset)
{
	t_point	proj;

	double angle = 0.5236;
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

void	draw_map(t_data *img, int ***map, int height, int width, double scale, int x_offset, int y_offset)
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
				continue;

			p0 = project_point(x, y, map[y][x][0], map[y][x][1], scale, x_offset, y_offset);

			if (x < width - 1 && map[y][x + 1])
			{
				p1 = project_point(x + 1, y, map[y][x + 1][0], map[y][x + 1][1], scale, x_offset, y_offset);
				draw_line(img, p0.x, p0.y, p1.x, p1.y, p0.color);
			}

			if (y < height - 1 && map[y + 1][x])
			{
				p1 = project_point(x, y + 1, map[y + 1][x][0], map[y + 1][x][1], scale, x_offset, y_offset);
				draw_line(img, p0.x, p0.y, p1.x, p1.y, p0.color);
			}
		}
	}
}


int	main(int ac, char **av)
{
	int		***map;
	int		height;
	int		width;
	double		scale;
	int		x_offset;
	int		y_offset;
	t_data	img;
	void	*mlx;
	void	*mlx_win;

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
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Ansebast's FdF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	scale = fmin(1920 / width, 1080 / height);
        if (scale <= 0)
                scale = 1;
        else if (scale > 20)
                scale /= 2;
        // x_offset = (1920 - (width * scale)) / 2;
        // y_offset = (1080 - (height * scale)) / 2;
        x_offset = (1920 / 2) - ((width * scale) / 2);
	y_offset = (1080 / 2) - ((height * scale) / 2);
	draw_map(&img, map, height, width, scale, x_offset, y_offset);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
