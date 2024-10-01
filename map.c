/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:56:50 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 20:02:43 by ansebast         ###   ########.fr       */
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
			vars->map[new_point.y][new_point.x][1] = get_color_from_altitude(vars->map[new_point.y][new_point.x][0],
					vars->z_min, vars->z_max);
			new_point.color = vars->map[new_point.y][new_point.x][1];
			new_point.z = vars->map[new_point.y][new_point.x][0];
			p0 = project_point(&new_point, vars);
			if (new_point.x < vars->width - 1 && vars->map[new_point.y][new_point.x + 1])
			{
				new_point.color = vars->map[new_point.y][new_point.x + 1][1];
				new_point.z = vars->map[new_point.y][new_point.x + 1][0];
                                new_point.x++;
				p1 = project_point(&new_point, vars);
				draw_line(&vars->img, p0, p1);
                                new_point.x--;
			}
			if (new_point.y < vars->height - 1 && vars->map[new_point.y + 1][new_point.x])
			{
				new_point.color = vars->map[new_point.y + 1][new_point.x][1];
				new_point.z = vars->map[new_point.y + 1][new_point.x][0];
                                new_point.y++;
				p1 = project_point(&new_point, vars);
				draw_line(&vars->img, p0, p1);
                                new_point.y--;
			}
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