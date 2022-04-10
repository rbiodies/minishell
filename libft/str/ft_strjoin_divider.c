/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_divider.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:40:24 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/25 15:44:45 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin_divider(char const *s1, char const *s2, char divider)
/* will append s2 to s1
** will do nothing if s1 or s2 is NULL
** this is a modified version, it will ad a '/' between the strings */
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	buffer = (char *)malloc(ft_len(s1) + ft_len(s2) + 2);
	if (buffer == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		buffer[i] = s1[i];
		i++;
	}
	buffer[i++] = divider;
	while (s2[j] != '\0')
	{
		buffer[i] = s2[j];
		i++;
		j++;
	}
	buffer[i] = '\0';
	return (buffer);
}
