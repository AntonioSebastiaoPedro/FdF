/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:54 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/14 19:03:45 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = current;
	}
}
