/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_our_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:05:41 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 14:04:16 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pwd(void)
{
	char	*pwd;
	char	buff[4096 + 1];

	pwd = getcwd(buff, 4096);
	ft_putendl_fd(pwd, 1);
	return (1);
}

static int	ft_env(char **tokens)
{
	int	i;

	i = 0;
	if (tokens[1] != NULL)
	{
		write(1, "env: ", 5);
		ft_putstr_fd(tokens[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	while (g_envp[i])
	{
		if (ft_strchr(g_envp[i], '=') != NULL)
			ft_putendl_fd(g_envp[i], 1);
		i++;
	}
	return (1);
}

/* 
ls f; echo $?; echo $?
status = 0  after echo $?
*/

int	ft_run_our_cmd(t_list *temp, t_his **history)
{
	if (ft_strcmp(temp->tokens[0], "echo") == 0)
	{
		ft_echo(temp);
		free((*history)->his);
		(*history)->his = ft_strdup("0");
		return (1);
	}
	else if (ft_strcmp(temp->tokens[0], "cd") == 0)
		return (ft_cd(temp->tokens[1], history));
	else if (ft_strcmp(temp->tokens[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(temp->tokens[0], "export") == 0)
		return (ft_export(temp->tokens));
	else if (ft_strcmp(temp->tokens[0], "unset") == 0)
		return (ft_unset(temp->tokens));
	else if (ft_strcmp(temp->tokens[0], "env") == 0)
		return (ft_env(temp->tokens));
	else if (ft_strcmp(temp->tokens[0], "history") == 0)
		return (ft_history_output(history));
	else if (ft_strcmp(temp->tokens[0], "exit") == 0)
		return (ft_exit(temp, history));
	return (0);
}

int	ft_check_our_cmd(char *token)
{
	if (token == NULL)
		return (0);
	else if (ft_strcmp(token, "echo") == 0)
		return (1);
	else if (ft_strcmp(token, "cd") == 0)
		return (1);
	else if (ft_strcmp(token, "pwd") == 0)
		return (1);
	else if (ft_strcmp(token, "export") == 0)
		return (1);
	else if (ft_strcmp(token, "unset") == 0)
		return (1);
	else if (ft_strcmp(token, "env") == 0)
		return (1);
	else if (ft_strcmp(token, "history") == 0)
		return (1);
	else if (ft_strcmp(token, "exit") == 0)
		return (1);
	return (0);
}
