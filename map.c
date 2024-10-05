/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:56:50 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/05 12:52:38 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_lines(const char *file, int *height)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		(*height)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

static int	***fill_map(const char *file, int height, int *width)
{
	int		fd;
	int		i;
	char	*line;
	int		***map;

	map = malloc(sizeof(int **) * height);
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i++] = parse_line(line, width);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

int	***read_map(const char *file, int *height, int *width)
{
	if (count_lines(file, height) < 0)
		return (NULL);
	return (fill_map(file, *height, width));
}

void	draw_map(t_vars *vars)
{
	t_point	p0;
	t_point	p1;
	t_point	new_point;

	new_point.y = 0;
	while (new_point.y < vars->height)
	{
		new_point.x = 0;
		while (new_point.x < vars->width)
		{
			if (!vars->map[new_point.y] || !vars->map[new_point.y][new_point.x])
				continue ;
			new_point.color = vars->map[new_point.y][new_point.x][1];
			new_point.z = vars->map[new_point.y][new_point.x][0];
			p0 = project_point(&new_point, vars);
			draw_horizontal_lines(vars, &new_point, &p0, &p1);
			draw_vertical_lines(vars, &new_point, &p0, &p1);
			new_point.x++;
		}
		new_point.y++;
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
