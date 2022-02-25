/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:55:20 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 16:49:48 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_not_path(t_list *temp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(temp->tokens[0], 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

static void	ft_add_history_error(t_his **history)
{
	free((*history)->his);
	(*history)->his = ft_strdup("127");
}

static int	ft_take_cmd(t_list *temp, t_his **history)
{
	char	*tmp;

	temp->cmd_with_path = ft_strdup(temp->tokens[0]);
	if (ft_strrchr(temp->tokens[0], '/') == NULL)
	{
		ft_add_history_error(history);
		free(temp->cmd_with_path);
		temp->cmd_with_path = NULL;
		return (0);
	}
	tmp = ft_strrchr(temp->tokens[0], '/') + 1;
	free(temp->tokens[0]);
	temp->tokens[0] = ft_strdup(tmp);
	return (1);
}

static char	**ft_init_paths(void)
{
	int		i;
	char	*path_envp;
	char	**paths_cmd;

	i = 0;
	while (g_envp[i] && ft_strncmp("PATH=", g_envp[i], 5))
		i++;
	if (g_envp[i] == NULL)
		return (NULL);
	path_envp = ft_strrchr(g_envp[i], '=') + 1;
	paths_cmd = ft_split(path_envp, ':');
	return (paths_cmd);
}

// check folder "ls"

int	ft_get_path(t_list *temp, t_his **history)
{
	char	**paths_cmd;
	int		i;

	if (access(temp->tokens[0], F_OK) == 0 \
	&& open(temp->tokens[0], O_DIRECTORY) == -1 && ft_take_cmd(temp, history))
		return (1);
	paths_cmd = ft_init_paths();
	if (!paths_cmd)
		return (ft_not_path(temp));
	i = -1;
	while (paths_cmd[++i])
	{
		temp->cmd_with_path \
		= ft_strjoin_divider(paths_cmd[i], temp->tokens[0], '/');
		if (access(temp->cmd_with_path, F_OK) == 0)
		{
			ft_strfree(paths_cmd);
			return (1);
		}
		free(temp->cmd_with_path);
		temp->cmd_with_path = NULL;
	}
	ft_add_history_error(history);
	ft_strfree(paths_cmd);
	return (0);
}
