/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:19:32 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/24 10:23:19 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_39(int *j, char **s, char **new)
{
	int	n;

	n = *j;
	(*new)[n] = **s;
	(*s)++;
	n++;
	while (**s != 39 && **s != '\0')
	{
		(*new)[n] = **s;
		(*s)++;
		n++;
	}
	(*new)[n] = **s;
	(*s)++;
	n++;
	*j = n;
}

void	fill_numb(char **new, char *numb, int *j, char **s)
{
	int	n;
	int	k;

	n = *j;
	k = 0;
	while (numb[k] != '\0')
	{
		(*new)[n] = numb[k];
		n++;
		k++;
	}
	*j = n;
	*s = *s + 2;
}

static void	fill_var1(char *str, char **new, int *j)
{
	int	k;
	int	n;

	k = 0;
	n = *j;
	while (g_envp[k] != NULL)
	{
		if (ft_strcmp_exp(g_envp[k], str) == 0)
		{
			free(str);
			str = ft_strchr(g_envp[k], '=');
			k = 0;
			while (str[++k] != '\0')
			{
				if (str[k] == ' ' && str[k - 1] == ' ')
					k++;
				else
					(*new)[n++] = str[k];
			}
			*j = n;
			return ;
		}
		k++;
	}
	free(str);
}

int	fill_var(int *j, char **s, char **new)
{
	char	*str;
	int		count;

	count = 0;
	str = *s;
	str++;
	while ((*str > 64 && *str < 91) || (*str > 96 && *str < 123) \
	|| (*str > 47 && *str < 58) || *str == 95)
	{
		str++;
		count++;
	}
	if (count == 0)
	{
		(*new)[*j] = **s;
		(*s)++;
		*j = *j + 1;
		return (1);
	}
	str = ft_create_str1(count, s);
	if (str == NULL)
		return (-1);
	fill_var1(str, new, j);
	return (1);
}

int	fill_34(int *j, char **s, char **new, t_his *history)
{
	ft_move(j, s, new);
	while (**s != 34 && **s != '\0')
	{
		if (**s == '$' && *(*s + 1) == '?')
			fill_numb(new, history->his, j, s);
		else if (**s == '$')
		{
			if (fill_var(j, s, new) == -1)
				return (-1);
		}
		else
			ft_move(j, s, new);
	}
	ft_move(j, s, new);
	return (0);
}
