/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:50:20 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 13:50:46 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
> > || < >
>> >>
<< <<
> < || >> < || < <
*/

static int	ft_check_redirect(t_list *temp)
{
	if ((temp->type == TYPE_TRUNC || temp->type == TYPE_INPUT) && temp->next \
	&& temp->next->tokens[0] == NULL && temp->next->type == TYPE_TRUNC)
		return (ft_syntax_error(">"));
	if (temp->type == TYPE_APPEND && temp->next \
	&& temp->next->tokens[0] == NULL && temp->next->type == TYPE_APPEND)
		return (ft_syntax_error(">>"));
	if (temp->type == TYPE_HEREDOC && temp->next \
	&& temp->next->tokens[0] == NULL && temp->next->type == TYPE_HEREDOC)
		return (ft_syntax_error("<<"));
	if ((temp->type == TYPE_APPEND || temp->type == TYPE_TRUNC \
	|| temp->type == TYPE_INPUT) && temp->next && temp->next->tokens[0] == NULL \
	&& temp->next->type == TYPE_INPUT)
		return (ft_syntax_error("<"));
	return (0);
}

/*
no args
|
;
redirects
> || >> || < || <<
*/

int	ft_check_arguments(t_list *temp)
{
	while (temp)
	{
		if (temp->tokens[0] == NULL && temp->type == TYPE_END)
			return (1);
		if (temp->tokens[0] == NULL && temp->type == TYPE_PIPE)
			return (ft_syntax_error("|"));
		if (temp->tokens[0] == NULL && temp->type == TYPE_BREAK)
			return (ft_syntax_error(";"));
		if (ft_check_redirect(temp) == 1)
			return (1);
		if ((temp->type == TYPE_TRUNC || temp->type == TYPE_APPEND \
		|| temp->type == TYPE_INPUT || temp->type == TYPE_HEREDOC) \
		&& temp->next == NULL)
			return (ft_syntax_error("newline"));
		temp = temp->next;
	}
	return (0);
}
