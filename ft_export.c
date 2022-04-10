/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:34:29 by bjeana            #+#    #+#             */
/*   Updated: 2022/04/10 11:03:22 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_action(int k, int *j, char *str)
{
	char	*re_envp;
	int		temp;

	temp = *j;
	re_envp = NULL;
	if (k == 1)
	{
		re_envp = ft_strdup(str);
		*j = temp - 1;
	}
	else if (k == 0)
		re_envp = ft_strdup(str);
	return (re_envp);
}

static char	**remake_envp(char *str, int k)
{
	int		i;
	int		j;
	int		n;
	char	**re_envp;

	i = -1;
	j = 0;
	n = ft_arrlen(g_envp) + k;
	re_envp = (char **)malloc((sizeof(char *) * n) + 1);
	if (re_envp == NULL)
		return (NULL);
	while (++i < n)
	{
		if (k == 1 && i == n - 2)
			re_envp[i] = ft_action(k, &j, str);
		else if (k == 0 && ft_strcmp_exp(g_envp[i], str) == 0)
			re_envp[i] = ft_action(k, &j, str);
		else
			re_envp[i] = ft_strdup(g_envp[j]);
		if (re_envp[i] == NULL)
			return (error(re_envp));
		j++;
	}
	re_envp[i] = NULL;
	return (re_envp);
}

static int	ft_just_export(void)
{
	int		i;
	char	*temp;
	char	**c_envp;

	i = 0;
	c_envp = remake_envp(NULL, -1);
	if (c_envp == NULL)
		return (-1);
	while (c_envp[i + 1] != NULL)
	{
		if (ft_strcmp_exp(c_envp[i], c_envp[i + 1]) > 0)
		{
			temp = c_envp[i];
			c_envp[i] = ft_strdup(c_envp[i + 1]);
			free(c_envp[i + 1]);
			c_envp[i + 1] = ft_strdup(temp);
			free(temp);
			i = 0;
		}
		else
			i++;
	}
	ft_putarr_export(c_envp);
	ft_arrfree(c_envp);
	return (1);
}

static int	ft_export_args(int m, char *token)
{
	char	**temp;

	temp = g_envp;
	if (m == 2)
		g_envp = remake_envp(token, 0);
	else if (m == 0)
		g_envp = remake_envp(token, 1);
	ft_arrfree(temp);
	if (g_envp == NULL)
		return (-1);
	return (1);
}

int	ft_export(char **token)
{
	int	m;
	int	k;
	int	i;

	i = 1;
	k = 1;
	if (ft_arrlen(token) == 1)
		return (ft_just_export());
	while (token[i] != NULL && k != -1)
	{
		if (valid_export1(token[i], token) != 1)
		{
			m = valid_export2(token[i]);
			if (m != 1)
				k = ft_export_args(m, token[i]);
		}
		i++;
	}
	return (k);
}
