/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:24 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 16:06:40 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_base(char **s, int base)
{
	if (base == 0)
	{
		if (**s == '0')
		{
			if ((*s)[1] == 'x' || (*s)[1] == 'X')
			{
				*s += 2;
				return (16);
			}
			else
			{
				(*s)++;
				return (8);
			}
		}
		return (10);
	}
	else if (base == 16 && **s == '0' && ((*s)[1] == 'x' || (*s)[1] == 'X'))
		*s += 2;
	return (base);
}

static int	ft_get_digit(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isalpha(c))
		return (ft_toupper(c) - 'A' + 10);
	return (-1);
}

long	ft_strtol(char *s, char **endptr, int base)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	base = ft_get_base(&s, base);
	while (*s)
	{
		digit = ft_get_digit(*s);
		if (digit < 0 || digit >= base)
			break ;
		result = result * base + digit;
		s++;
	}
	if (endptr)
		*endptr = (char *)(s);
	return (result * sign);
}
