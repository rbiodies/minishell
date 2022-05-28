/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:55:52 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 10:30:38 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if "ls no_file"

static void	ft_parent(t_list *temp, pid_t pid, int pipe_open, t_his **history)
{
	int		status;

	waitpid(pid, &status, 0);
	free((*history)->his);
	if ((ft_strcmp(temp->tokens[0], "cat") == 0 \
	|| ft_strcmp(temp->tokens[0], "ls") == 0 \
	|| ft_strcmp(temp->tokens[0], "cd") == 0) \
	&& temp->tokens[1] && access(temp->tokens[1], F_OK) != 0)
		(*history)->his = ft_strdup("1");
	else if (ft_strcmp(temp->tokens[0], "exit") == 0 && temp->tokens[1])
		(*history)->his = ft_strdup(temp->tokens[1]);
	else
		(*history)->his = ft_itoa(status);
	if (pipe_open == 1)
	{
		close(temp->fd[STDOUT]);
		if (!temp->next || temp->type == TYPE_BREAK)
			close(temp->fd[STDIN]);
	}
	unlink("../pipe_file");
	if (temp->prev && temp->prev->type == TYPE_PIPE)
		close(temp->prev->fd[STDIN]);
}

static void	ft_child(t_list *temp, t_his **history)
{
	if (temp->type == TYPE_TRUNC || temp->type == TYPE_APPEND)
		ft_file_after_cmd_and_redirect(temp, history);
	else if (temp->type == TYPE_INPUT)
		ft_file_after_cmd_and_redirect_input(temp, history);
	else if (temp->tokens[0] != NULL && temp->type == TYPE_HEREDOC \
	&& temp->next)
		ft_heredoc(temp, history);
	else
		ft_cmd_and_pipe(temp, history);
	exit(EXIT_SUCCESS);
}

int	ft_run_cmd(t_list *temp, t_his **history)
{
	int		pipe_open;
	pid_t	pid;

	pipe_open = 0;
	if (temp->type == TYPE_PIPE || (temp->prev \
	&& temp->prev->type == TYPE_PIPE) || temp->type == TYPE_TRUNC \
	|| temp->type == TYPE_APPEND || temp->type == TYPE_HEREDOC \
	|| temp->type == TYPE_INPUT)
	{
		pipe_open = 1;
		if (pipe(temp->fd))
			return (-1);
	}
	pid = fork();
	signal(SIGINT, ft_proc_signal_handler);
	if (pid < 0)
	{
		ft_putendl_fd("Fork failed to create a new process.", 1);
		return (-1);
	}
	else if (pid == 0)
		ft_child(temp, history);
	else
		ft_parent(temp, pid, pipe_open, history);
	return (0);
}
