/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:27:45 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 10:22:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isvalid_digit(int ch, int baselen)
{
	char	*lcbase;
	char	*ucbase;
	int		i;

	lcbase = "0123456789abcdef";
	ucbase = "0123456789ABCDEF";
	i = 0;
	while (i < baselen)
	{
		if (ch == lcbase[i] || ch == ucbase[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	ft_convert_digits(char *str, int i, long *res, int str_base)
{
	while (str[i] && ft_isvalid_digit(str[i], str_base))
	{
		*res *= str_base;
		if (str[i] >= '0' && str[i] <= '9')
			*res += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			*res += str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			*res += str[i] - 'A' + 10;
		i++;
	}
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	ft_convert_digits((char *)str, i, (long *)&res, str_base);
	return (res * sign);
}
