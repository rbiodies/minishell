/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_my.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:20:41 by rbiodies          #+#    #+#             */
/*   Updated: 2022/01/17 16:20:43 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_my(t_list **lst)
{
	t_list	*tmp;
	t_list	*element;

	element = *lst;
	tmp = NULL;
	if (!lst || !*lst)
		return ;
	while (element)
	{
		if (element->next)
			tmp = element->next;
		else
			tmp = NULL;
		if (element->content != 0)
			element->content = 0;
		free(element);
		element = tmp;
	}
	*lst = NULL;
}
