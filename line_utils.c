/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:02:07 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 19:31:33 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	init_algo_vars(t_bresenham *alg, t_point *p0, t_point *p1)
{
	alg->dx = ft_abs(p1->x - p0->x);
	alg->dy = ft_abs(p1->y - p0->y);
	if (p0->x < p1->x)
		alg->sx = 1;
	else
		alg->sx = -1;
	if (p0->y < p1->y)
		alg->sy = 1;
	else
		alg->sy = -1;
	alg->err = alg->dx - alg->dy;
}

void	draw_line(t_data *img, t_point p0, t_point p1)
{
	t_bresenham alg;

	init_algo_vars(&alg, &p0, &p1);
	while (1)
	{
		my_mlx_pixel_put(img, p0.x, p0.y, p0.color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		alg.e2 = 2 * alg.err;
		if (alg.e2 > -alg.dy)
		{
			alg.err -= alg.dy;
			p0.x += alg.sx;
		}
		if (alg.e2 < alg.dx)
		{
			alg.err += alg.dx;
			p0.y += alg.sy;
		}
	}
}
