/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:13:17 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/02 21:28:52 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer_exit(t_list **list, t_list **new, char *line, t_his **history)
{
	if (*new != NULL)
		ft_lstfree(new);
	ft_putendl_fd("error: fatal", 2);
	free(line);
	ft_lstfree(list);
	ft_free(history);
	exit(EXIT_FAILURE);
}

void	ft_quotes(t_list **list, t_list *new, char *line, t_his **history)
{
	int	j;

	j = 0;
	while (new->tokens[j])
	{
		new->tokens[j] = ft_check_quotes(new->tokens[j]);
		if (new->tokens[j] == NULL)
			ft_lexer_exit(list, &new, line, history);
		j++;
	}
}
