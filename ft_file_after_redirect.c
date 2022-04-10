/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_after_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:21:37 by rbiodies          #+#    #+#             */
/*   Updated: 2022/04/10 11:02:13 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fdout_error(t_list *temp2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(temp2->next->tokens[0], 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

/* 
> a ls
->
ls > a
*/

static int	ft_cmd_after_file_and_redirect(t_list *temp, t_list *temp2)
{
	int	i;

	ft_arrfree(temp->tokens);
	temp->tokens = (char **)malloc(sizeof(char *) * ft_arrlen(temp2->tokens));
	i = 1;
	while (temp2->tokens[i])
	{
		temp->tokens[i - 1] = ft_strdup(temp2->tokens[i]);
		free(temp2->tokens[i]);
		temp2->tokens[i] = NULL;
		i++;
	}
	temp->tokens[i - 1] = NULL;
	return (0);
}

/* 
> F1
> F1 > f2
> F1 echo lol
< F1
*/

int	ft_file_after_redirect(t_list *temp)
{
	t_list	*temp2;
	int		fdout;

	temp2 = temp;
	while (temp2->type == TYPE_APPEND || temp2->type == TYPE_TRUNC \
	|| temp2->type == TYPE_INPUT)
	{
		if (temp2->type == TYPE_TRUNC)
			fdout = \
			open(temp2->next->tokens[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp2->type == TYPE_APPEND)
			fdout = \
			open(temp2->next->tokens[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (temp2->type == TYPE_INPUT)
			fdout = open(temp2->next->tokens[0], O_RDONLY);
		if (fdout == -1)
			return (ft_fdout_error(temp2));
		close(fdout);
		temp2 = temp2->next;
	}
	if (temp2->tokens[1] != NULL)
		return (ft_cmd_after_file_and_redirect(temp, temp2));
	return (1);
}
