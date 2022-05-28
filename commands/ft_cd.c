/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:39:20 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 10:27:20 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if run "cd -" in start minishell with no OLDPWD

static char	*ft_getenv(char *key)
{
	int		i;
	char	*tmp;
	char	*pwd;
	char	buff[4096 + 1];
	char	*old_new_pwd;

	i = -1;
	while (g_envp[++i])
	{
		tmp = ft_strjoin(key, "=");
		if (ft_strncmp(tmp, g_envp[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			pwd = getcwd(buff, 4096);
			old_new_pwd = ft_strchr(g_envp[i], '=') + 1;
			if (ft_strcmp(old_new_pwd, "") == 0)
			{
				ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
				return (NULL);
			}
			return (old_new_pwd);
		}
		free (tmp);
	}
	return (NULL);
}

static int	ft_find_oldpwd(char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_envp[i])
	{
		tmp = ft_strjoin(key, "=");
		if (ft_strncmp(tmp, g_envp[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (i);
}

static void	ft_change_oldpwd(char *key, char *new_old_pwd)
{
	int		pos;
	char	*tmp;

	pos = ft_find_oldpwd(key);
	tmp = ft_strjoin(key, "=");
	free(g_envp[pos]);
	g_envp[pos] = ft_strjoin(tmp, new_old_pwd);
	free(tmp);
}

void	ft_change_dir(char *path, int print_path, t_his **history)
{
	char	*new_old_path;
	char	buff[4097];

	if (path == NULL)
		return ;
	new_old_path = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (print_path)
			ft_putendl_fd(path, 1);
		ft_change_oldpwd("OLDPWD", new_old_path);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		if (access(path, F_OK) == -1)
			ft_putendl_fd(": No such file or directory", 2);
		else if (access(path, R_OK) == -1)
			ft_putendl_fd(": Permission denied", 2);
		else
			ft_putendl_fd(": Not a directory", 2);
		free((*history)->his);
		(*history)->his = ft_strdup("1");
	}
}

int	ft_cd(char *token, t_his **history)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (!token)
	{
		ft_change_dir(home_path, 0, history);
		return (1);
	}
	if (ft_strcmp(token, "--") == 0 || ft_strcmp(token, "~") == 0)
	{
		ft_change_dir(home_path, 0, history);
		return (1);
	}
	else if (token[0] == '-' && !token[1])
	{
		ft_change_dir(ft_getenv("OLDPWD"), 1, history);
		return (1);
	}
	ft_change_dir(token, 0, history);
	return (1);
}
