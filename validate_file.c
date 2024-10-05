/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:48:09 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/05 12:15:31 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	check_file(char *path_file)
{
	char	*extension;
	int		len;

	extension = ft_strrchr(path_file, '.');
	if (!extension || ft_strncmp(extension, ".fdf", 4))
		ft_puterror("Invalid file.\n", 1);
	len = len_line_file(path_file);
	if (len == -1)
		ft_puterror("Error opening file.\n", 1);
	if (len == 0)
		ft_puterror("The file is empty.\n", 1);
	if (check_wrong_lines(path_file))
		ft_puterror("Found wrong line length.\n", 1);
}

int	ft_countarray(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (len);
	while (array[len])
	{
		free(array[len]);
		len++;
	}
	free(array);
	return (len);
}

int	len_line_file(char *path_file)
{
	int		fd;
	int		len;
	char	*line;

	fd = open(path_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		len++;
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

int	check_wrong_lines(char *path_file)
{
	int		fd;
	int		len_line;
	char	*line;
	char	**spl;

	fd = open(path_file, O_RDONLY);
	line = get_next_line(fd);
	spl = ft_split(line, ' ');
	len_line = ft_countarray(spl);
	while (line)
	{
		spl = ft_split(line, ' ');
		if (len_line != ft_countarray(spl))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
