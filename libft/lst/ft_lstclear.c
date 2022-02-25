/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:44:58 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/17 15:06:47 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*element;

	element = *lst;
	if (*lst == NULL)
		return ;
	while (element != NULL)
	{
		tmp = element->next;
		del(element->content);
		free(element);
		element = tmp;
	}
	*lst = NULL;
}
