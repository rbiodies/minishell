/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:09:10 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 10:28:04 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_digits(t_list *temp)
{
	int	i;

	i = 0;
	if (temp->tokens[1] \
	&& (temp->tokens[1][i] == '-' || temp->tokens[1][i] == '+'))
			i++;
	while (temp->tokens[1] && temp->tokens[1][i] != '\0')
	{
		if (temp->tokens[1][i] < '0' || temp->tokens[1][i] > '9')
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(temp->tokens[1], STDERR);
			ft_putendl_fd(": numeric argument required", STDERR);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_list *temp, t_his **history)
{
	if (ft_check_digits(temp) == -1)
	{
		free((*history)->his);
		(*history)->his = ft_strdup("255");
		return (-1);
	}
	if (temp->tokens[1])
	{
		free((*history)->his);
		(*history)->his = ft_strdup(temp->tokens[1]);
	}
	if (temp->prev && temp->prev->type == TYPE_PIPE)
		return (-1);
	ft_putendl_fd("exit", 1);
	return (-1);
}
