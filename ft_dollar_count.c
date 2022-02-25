/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:31:47 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/24 10:47:11 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_str(int count, int *i, char *s)
{
	int		k;
	int		j;
	char	*str;

	k = 0;
	j = *i + 1;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (NULL);
	while (k < count)
	{
		str[k] = s[j];
		j++;
		k++;
	}
	str[k] = '\0';
	return (str);
}

int	ft_strlen_var(char *str, int *flag)
{
	int	k;
	int	count;

	k = 0;
	count = 0;
	while (g_envp[k] != NULL)
	{
		*flag = 2;
		if (ft_strcmp_exp(g_envp[k], str) == 0)
		{
			free(str);
			str = ft_strchr(g_envp[k], '=');
			count = ft_strlen_dollar(str + 1);
			if (str[0] == '\0')
				*flag = 2;
			else
				*flag = 1;
			return (count);
		}
		k++;
	}
	free(str);
	return (count);
}

static int	ft_while(int *i, char *s)
{
	int	count;
	int	k;

	count = 0;
	k = *i;
	while ((s[++k] > 64 && s[k] < 91) || (s[k] > 96 && s[k] < 123) \
	|| (s[k] > 47 && s[k] < 58) || s[k] == 95)
		count++;
	*i = k;
	return (count);
}

int	ft_len_var(char *s, int *i, int *flag, t_his *history)
{
	char	*str;
	int		count;
	int		k;

	k = *i;
	count = 0;
	if (s[k + 1] == '?')
	{
		*flag = 1;
		*i = k + 2;
		return (ft_strlen(history->his));
	}
	count = ft_while(&k, s);
	if (count == 0)
	{
		*i = *i + 1;
		return (1);
	}
	str = ft_create_str(count, i, s);
	if (str == NULL)
		return (-1);
	*i = k;
	if (s[k] != '\0')
		*i = k - 1;
	return (ft_strlen_var(str, flag));
}

int	ft_check_dollar(char *s, int *flag, t_his *history, int count)
{
	int	i;
	int	ret;

	i = -1;
	while (s[++i] != '\0')
	{
		ret = 0;
		if (s[i] == 39)
			count = ft_39(s, &i, count);
		else if (s[i] == '$')
		{
			ret = ft_len_var(s, &i, flag, history);
			count = count + ret;
		}
		else if (s[i] == 34)
		{
			ret = ft_34(s, &i, flag, history);
			count = count + ret;
		}
		if (ret == -1)
			return (-1);
		if (s[i] != '\0' && ret == 0)
			count++;
	}
	return (count);
}
