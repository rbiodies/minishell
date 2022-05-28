/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 13:54:02 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 13:50:29 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmd_not_found(t_list *temp)
{
	if (temp->type == TYPE_APPEND || temp->type == TYPE_TRUNC)
		ft_file_after_redirect(temp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(temp->tokens[0], 2);
	ft_putendl_fd(": command not found", 2);
	return (0);
}

/*
error for full path only 
example: /bin/libft 
not libft

struct stat is used for get info
lstat return info about a file
st_mode is bites chmod, type and special bites of a file
*/

static int	ft_directory_without_cd(t_list *temp)
{
	struct stat	f;

	if (ft_strchr(temp->tokens[0], '/') != NULL \
	&& lstat(temp->tokens[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp->tokens[0], 2);
			ft_putendl_fd(": is a directory", 2);
			return (1);
		}
	}
	return (0);
}

static int	ft_executor_cmd(t_list *temp, t_his **history)
{
	int	is_redirect;
	int	is_path;

	if (ft_check_arguments(temp) == 1)
		return (2);
	if (ft_check_our_cmd(temp->tokens[0]) == 1 \
	&& temp->type != TYPE_PIPE && temp->type != TYPE_INPUT \
	&& temp->type != TYPE_APPEND && temp->type != TYPE_TRUNC \
	&& (temp->prev == NULL || (temp->prev && temp->prev->type != TYPE_PIPE)))
		return (ft_run_our_cmd(temp, history));
	is_redirect = ft_redirect(temp, history);
	if (is_redirect == 1)
		return (0);
	is_path = ft_get_path(temp, history);
	if (is_path == -1 || is_redirect == -1)
		return (-1);
	if ((is_path == 1 || ft_check_our_cmd(temp->tokens[0]) == 1))
		return (ft_run_cmd(temp, history));
	if (ft_directory_without_cd(temp) == 1)
		return (0);
	return (ft_cmd_not_found(temp));
}

// status = 1 for ft_run_our_cmd

int	ft_executor(t_list **list, t_his **history)
{
	t_list	*temp;
	int		status;

	temp = *list;
	while (temp)
	{
		status = ft_executor_cmd(temp, history);
		if (status == -1)
			break ;
		if (status == 2)
		{
			free((*history)->his);
			(*history)->his = ft_strdup("258");
			break ;
		}
		while (temp->type == TYPE_APPEND || temp->type == TYPE_TRUNC \
		|| temp->type == TYPE_INPUT)
			temp = temp->next;
		temp = temp->next;
	}
	ft_lstfree(list);
	return (status);
}
