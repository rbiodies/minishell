/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:03:55 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/24 14:04:34 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hisclear(t_his **lst)
{
	t_his	*temp;
	t_his	*nxt;

	temp = *lst;
	while (temp != NULL)
	{
		nxt = temp->next;
		free(temp->his);
		free(temp);
		temp = nxt;
	}
	*lst = NULL;
}

static t_his	*ft_history_new(char *his)
{
	t_his	*new;

	new = (t_his *)malloc(sizeof(t_his) * 1);
	if (new == NULL)
		return (NULL);
	new->his = his;
	new->next = NULL;
	return (new);
}

static void	ft_historyadd_back(t_his **lst, t_his *new)
{
	t_his	*temp;

	temp = *lst;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

int	ft_add_history(char *line, t_his **history)
{
	t_his	*new;

	new = ft_history_new(ft_strdup(line));
	if (new == NULL)
		return (-1);
	ft_historyadd_back(history, new);
	return (1);
}

int	ft_history_output(t_his **history)
{
	int		i;
	t_his	*temp;

	i = 1;
	temp = *history;
	temp = temp->next;
	while (temp != NULL)
	{
		ft_putnbr_fd(i, 1);
		write(1, "  ", 1);
		ft_putendl_fd(temp->his, 1);
		i++;
		temp = temp->next;
	}
	return (1);
}
