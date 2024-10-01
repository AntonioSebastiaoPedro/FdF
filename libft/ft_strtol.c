/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:24 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/01 15:40:56 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strtol(char *str, char **endptr, int base)
{
	int		i;
	int		signal;
	long	num;

	signal = 1;
	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		signal = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isvalid_digit(str[i], base))
	{
		num *= base;
		if (str[i] >= '0' && str[i] <= 9)
			num += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			num += str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			num += str[i] - 'A' + 10;
		i++;
	}
	*endptr = &str[i];
	return (num * signal);
}
