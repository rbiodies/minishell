/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:27:02 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/21 09:55:36 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstfree(t_list **list)
{
	t_list	*element;
	t_list	*temp;
	int		i;

	element = *list;
	while (element)
	{
		temp = element->next;
		i = 0;
		while (element->tokens[i])
		{
			free(element->tokens[i]);
			i++;
		}
		free(element->argv);
		free(element->tokens);
		free(element->cmd_with_path);
		free(element);
		element = temp;
	}
	*list = NULL;
}
