/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:56:50 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 18:55:52 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
				draw_line(&vars->img, p0, p1);
			}
			if (y < vars->height - 1 && vars->map[y + 1][x])
			{
				p1 = project_point(x, y + 1, vars->map[y + 1][x][0], vars->map[y
						+ 1][x][1], vars);
				draw_line(&vars->img, p0, p1);
			}
		}
	}
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