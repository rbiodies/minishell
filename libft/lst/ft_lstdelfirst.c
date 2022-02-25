/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:29:25 by rbiodies          #+#    #+#             */
/*   Updated: 2021/11/19 11:24:34 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelfirst(t_list **a)
{
	t_list	*tmp;

	if (a == NULL || *a == NULL)
		return ;
	tmp = *a;
	*a = (*a)->next;
	free(tmp);
}
