/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:43:56 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/04 15:20:41 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearray(char **array, int pos)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < pos)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}
