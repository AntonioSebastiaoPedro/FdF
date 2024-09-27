/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:30:48 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/27 13:36:56 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wdlen(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	*ft_get_word(char const *s, int *i, char c)
{
	int		word_len;
	char	*word;

	word_len = 0;
	while (s[*i + word_len] && s[*i + word_len] != c)
		word_len++;
	word = ft_substr(s, *i, word_len);
	*i += word_len;
	return (word);
}

static void	ft_freearray(char **array, int pos)
{
	while (pos > 0)
		free(array[--pos]);
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = (char **)ft_calloc((ft_wdlen(s, c) + 1), sizeof(char *));
	if (!s || !tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_get_word(s, &i, c);
			if (!tab[j++])
			{
				ft_freearray(tab, j);
				return (NULL);
			}
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
