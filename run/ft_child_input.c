/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:45:08 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 10:34:12 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fd_error(t_list *temp2)
{
	if (temp2->next->tokens[0][0] == '$')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp2->next->tokens[0], 2);
		ft_putendl_fd(": ambiguous redirect", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp2->next->tokens[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	exit(EXIT_FAILURE);
}

// echo lol > a ; cat < a > b > c # b empty

static void	ft_trunc_after_redirect_and_file(t_list *temp2)
{
	int		fdout;

	while (temp2->type == TYPE_APPEND || temp2->type == TYPE_TRUNC)
	{
		fdout = \
		open(temp2->next->tokens[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fdout == -1)
			ft_fd_error(temp2);
		temp2 = temp2->next;
		if (dup2(fdout, STDOUT) < 0)
			return (perror("dup2 failed"));
		close(fdout);
	}
}

/*
cat < a
cat < Makefile | grep gcc # don't work
cat < f1 < f2
*/

void	ft_file_after_cmd_and_redirect_input(t_list *temp, t_his **history)
{
	t_list	*temp2;
	int		fdin;

	temp2 = temp;
	while (temp2->type == TYPE_INPUT)
	{
		fdin = open(temp2->next->tokens[0], O_RDONLY);
		if (fdin == -1)
			ft_fd_error(temp2);
		temp2 = temp2->next;
	}
	if (temp2->type == TYPE_PIPE)
	{
		if (dup2(temp->fd[STDOUT], STDOUT) < 0)
		{
			ft_putendl_fd("error: fatal", STDERR);
			exit(EXIT_FAILURE);
		}
	}
	ft_trunc_after_redirect_and_file(temp2);
	if (dup2(fdin, STDIN) < 0)
		return (perror("dup2 failed"));
	close(fdin);
	ft_run(temp, history);
}
