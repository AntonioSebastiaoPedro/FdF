/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:40:53 by ansebast          #+#    #+#             */
/*   Updated: 2024/09/27 13:00:25 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_buffer(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	while (i < len1 + len2)
	{
		new_str[i] = s2[i - len1];
		i++;
	}
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

static char	*find_newline(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (NULL);
}

static char	*read_and_append(int fd, char **result)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!find_newline(*result))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		*result = join_buffer(*result, buffer);
	}
	free(buffer);
	return (*result);
}

static void	handle_remaining(char **result, char **remaining)
{
	char	*newline_pos;

	newline_pos = find_newline(*result);
	if (newline_pos)
	{
		*newline_pos = '\0';
		*remaining = ft_strdup(newline_pos + 1);
		*result = join_buffer(*result, "\n");
	}
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remaining)
		result = ft_strdup(remaining);
	else
		result = ft_strdup("");
	free(remaining);
	remaining = NULL;
	if (!read_and_append(fd, &result))
		return (NULL);
	handle_remaining(&result, &remaining);
	if (ft_strlen(result) == 0 && !remaining)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
