/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:34:27 by bjeana            #+#    #+#             */
/*   Updated: 2022/01/26 15:54:11 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_letter(char *s, char c, int i)
{
	while (s[++i] != c && s[i] != '\0')
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34 && s[i] != '\0')
				i++;
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i] != '\0')
				i++;
		}
	}
	return (i);
}

char	*handler_quote(char *s, char c)
{
	while (*s != c && *s != '\0')
	{
		if (*s == 34)
		{
			s++;
			while (*s != 34 && *s != '\0')
				s++;
		}
		else if (*s == 39)
		{
			s++;
			while (*s != 39 && *s != '\0')
				s++;
		}
		s++;
	}
	return (s);
}
