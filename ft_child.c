/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:03:04 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 14:48:57 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ls libft > a objects
->
ls libft objects > a objects
*/

static void	ft_file_after_file_redirect_and_cmd(t_list *temp, t_list *temp2)
{
	int	i;
	int	j;

	i = 1;
	while (temp->tokens[i])
		i++;
	j = 1;
	while (temp2->tokens[j])
	{
		temp->tokens[i] = ft_strdup(temp2->tokens[j]);
		i++;
		j++;
	}
	temp->tokens[i] = NULL;
}

static int	ft_fdout(t_list *temp)
{
	t_list	*temp2;
	int		fdout;

	temp2 = temp;
	fdout = -1;
	while (temp2->type == TYPE_TRUNC || temp2->type == TYPE_APPEND)
	{
		if (temp2->type == TYPE_TRUNC && temp2->next->tokens[0][0] != '$')
			fdout = \
			open(temp2->next->tokens[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp2->type == TYPE_APPEND && temp2->next->tokens[0][0] != '$')
			fdout = \
			open(temp2->next->tokens[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fdout == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp2->next->tokens[0], 2);
			ft_putendl_fd(": ambiguous redirect", 2);
			return (-1);
		}
		temp2 = temp2->next;
	}
	ft_file_after_file_redirect_and_cmd(temp, temp2);
	return (fdout);
}

/* 
echo test > a
ls | grep ft_cd.c > a
*/

void	ft_file_after_cmd_and_redirect(t_list *temp, t_his **history)
{
	int	fdout;

	fdout = ft_fdout(temp);
	if (fdout == -1)
		return ;
	if (temp->prev && temp->prev->type == TYPE_PIPE)
	{
		if (temp->prev->prev && temp->prev->prev->type == TYPE_INPUT)
		{
			if (dup2(temp->prev->prev->fd[STDIN], STDIN) < 0)
			{
				ft_putendl_fd("error: fatal", STDERR);
				exit(EXIT_FAILURE);
			}
		}
		else if (dup2(temp->prev->fd[STDIN], STDIN) < 0)
		{
			ft_putendl_fd("error: fatal", STDERR);
			exit(EXIT_FAILURE);
		}
	}
	if (dup2(fdout, STDOUT) < 0)
		return (perror("dup2 failed"));
	close(fdout);
	ft_run(temp, history);
}

void	ft_run(t_list *temp, t_his **history)
{
	if (ft_check_our_cmd(temp->tokens[0]) == 1)
	{
		if (ft_run_our_cmd(temp, history) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (execve(temp->cmd_with_path, temp->tokens, g_envp) < 0)
		exit(EXIT_FAILURE);
}

/*
ls
ls | grep ft_cd.c
*/

void	ft_cmd_and_pipe(t_list *temp, t_his **history)
{
	if (temp->type == TYPE_PIPE && dup2(temp->fd[STDOUT], STDOUT) < 0)
	{
		ft_putendl_fd("error: fatal", STDERR);
		exit(EXIT_FAILURE);
	}
	if (temp->prev && temp->prev->type == TYPE_PIPE \
	&& temp->prev->prev && temp->prev->prev->type == TYPE_INPUT \
	&& dup2(temp->prev->prev->fd[STDIN], STDIN) < 0)
	{
		ft_putendl_fd("error: fatal", STDERR);
		exit(EXIT_FAILURE);
	}
	if (temp->prev && temp->prev->type == TYPE_PIPE \
	&& dup2(temp->prev->fd[STDIN], STDIN) < 0)
	{
		ft_putendl_fd("error: fatal", STDERR);
		exit(EXIT_FAILURE);
	}
	ft_run(temp, history);
}
