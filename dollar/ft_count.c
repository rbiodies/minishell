/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:27:41 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/24 10:32:14 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_39(char *s, int *i, int count)
{
	int	k;

	k = *i;
	count++;
	k++;
	while (s[k] != 39 && s[k] != '\0')
	{
		k++;
		count++;
	}
	*i = k;
	return (count);
}

int	ft_34(char *s, int *i, int *flag, t_his *history)
{
	int	k;
	int	count;
	int	ret;

	k = *i;
	k++;
	count = 1;
	while (s[k] != 34 && s[k] != '\0')
	{
		if (s[k] == '$')
		{
			ret = ft_len_var(s, &k, flag, history);
			if (ret == -1)
				return (-1);
			count = count + ret;
		}
		count++;
		k++;
	}
	*i = k;
	return (count);
}

int	ft_strlen_dollar(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (i > 0 && s[i] == ' ' && s[i - 1] == ' ')
			i++;
		else
			len++;
		i++;
	}
	return (len);
}
