/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_my.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:06:10 by rbiodies          #+#    #+#             */
/*   Updated: 2022/01/16 12:04:06 by rbiodies         ###   ########.fr       */
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
