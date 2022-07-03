/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:51:55 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/24 10:45:34 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *str)
{
	int	i;
	int	one;

	one = 0;
	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] == 39)
		{
			one++;
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
		}
		else if (str[i] == 34)
		{
			one++;
			i++;
			while (str[i] != 34 && str[i] != '\0')
				i++;
		}
		if (str[i] == 39 || str[i] == 34)
			one++;
	}
	return (one);
}

static void	fill_str(char *str, int j, int len, char **s)
{
	int	i;

	i = -1;
	while (j < len)
	{
		if (str[++i] == 34)
		{
			if (str[i + 1] == '\0')
				(*s)[++j] = str[i];
			while (str[++i] != 34 && str[i] != '\0')
				(*s)[++j] = str[i];
		}
		else if (str[i] == 39)
		{
			if (str[i + 1] == '\0')
				(*s)[++j] = str[i];
			while (str[++i] != 39 && str[i] != '\0')
				(*s)[++j] = str[i];
		}
		else
			(*s)[++j] = str[i];
	}
	(*s)[++j] = '\0';
}

static char	*delete_quotes(char *str, int count)
{
	char	*s;
	int		j;
	int		len;

	j = -1;
	len = ft_strlen(str) - count;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	fill_str(str, j, len, &s);
	return (s);
}

char	*ft_check_quotes(char *s)
{
	char	*temp;
	int		count;

	temp = s;
	count = count_quotes(s);
	if (count == 0)
		return (s);
	s = delete_quotes(s, count);
	free(temp);
	return (s);
}
