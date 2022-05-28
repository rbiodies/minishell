/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:51:56 by bjeana            #+#    #+#             */
/*   Updated: 2022/04/10 11:02:30 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**error(char **arr)
{
	if (arr != NULL)
		ft_arrfree(arr);
	return (NULL);
}

int	ft_strcmp_exp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' && s1[i] != '=') || (s2[i] != '\0' && s2[i] != '='))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static char	**ft_delete_str(char *str)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = (char **)malloc(sizeof(char *) * ft_arrlen(g_envp));
	if (temp == NULL)
		return (NULL);
	while (g_envp[i] != NULL)
	{
		if (ft_strcmp_exp(g_envp[i], str) != 0)
		{
			temp[j] = ft_strdup(g_envp[i]);
			if (temp[j] == NULL)
				return (error(temp));
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	return (temp);
}

int	ft_unset(char **token)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	while (token[++i] != NULL)
	{
		j = -1;
		temp = g_envp;
		if (valid_export1(token[i], token) != 1)
		{
			while (g_envp[++j] != NULL)
			{
				if (ft_strcmp_exp(g_envp[j], token[i]) == 0)
				{
					g_envp = ft_delete_str(token[i]);
					ft_arrfree(temp);
					if (g_envp == NULL)
						return (-1);
					break ;
				}
			}
		}
	}
	return (1);
}
