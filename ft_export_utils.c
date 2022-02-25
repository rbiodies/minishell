/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:07 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/23 17:26:17 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putarr_export(char **str)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	while (str[++i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		c = 0;
		while (str[i][++j] != '\0')
		{
			write(1, &str[i][j], 1);
			if (str[i][j] == '=' && c == 0)
			{
				write(1, "\"", 1);
				c = 1;
			}
			if (str[i][j + 1] == '\"')
				write(1, "\\", 1);
		}
		if (c != 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
}

int	valid_export1(char *str, char **s)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (str[0] != '_' && (str[0] <= 64 || str[0] >= 91) \
	&& (str[0] <= 96 || str[0] >= 123) && str[0] != 39 && str[0] != 34)
		error = 1;
	while (str[++i] != '\0' && str[i] != '=')
	{
		if (str[i] != '_' && (str[i] <= 64 || str[i] >= 91) \
		&& (str[i] <= 96 || str[i] >= 123) && (str[i] <= 47 || str[i] >= 58) \
		&& str[i] != 39 && str[i] != 34)
			error = 1;
	}
	if (error == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s[0], 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	return (error);
}

int	valid_export2(char *str)
{
	int	i;

	i = 0;
	while (g_envp[i] != NULL)
	{
		if (ft_strcmp_exp(g_envp[i], str) == 0)
		{
			if (ft_strchr(str, '=') == NULL)
				return (1);
			else
				return (2);
		}
		i++;
	}
	return (0);
}
