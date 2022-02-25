/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:23:57 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/17 15:09:14 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*list;

	list = (struct s_list *)malloc(sizeof(struct s_list));
	if (list == NULL)
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}
