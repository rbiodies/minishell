/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:10 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/22 16:31:07 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_n(char **tokens)
{
	int	i;
	int	j;

	i = 1;
	while (tokens[i])
	{
		j = 0;
		if (tokens[i][j] == '-')
		{
			j = 1;
			while (tokens[i][j] == 'n')
				j++;
		}
		if (tokens[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

// echo test1 > a test2

int	ft_echo(t_list *temp)
{
	int	i;

	i = ft_check_n(temp->tokens);
	while (temp->tokens[i] != NULL)
	{
		ft_putstr_fd(temp->tokens[i], 1);
		if (temp->tokens[i + 1] != NULL || ((temp->type == TYPE_TRUNC \
		|| temp->type == TYPE_APPEND) && temp->next->tokens[1]))
			write(1, " ", 1);
		i++;
	}
	if (temp->tokens[1] && temp->tokens[1][0] == '-')
	{
		i = 1;
		while (temp->tokens[1][i] == 'n')
			i++;
		if (temp->tokens[1][i - 1] == 'n' && temp->tokens[1][i] == '\0')
			return (1);
	}
	write(1, "\n", 1);
	return (1);
}
