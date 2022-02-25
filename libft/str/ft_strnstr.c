/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:55:22 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/16 13:29:14 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	if (needle[j] == ' ' || needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len != 0)
	{
		length = len;
		while (haystack[i + j] != '\0' && len != 0 \
				&& haystack[i + j] == needle[j])
		{
			j++;
			len--;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
		len = length;
		len--;
	}
	return ((void *)0);
}
