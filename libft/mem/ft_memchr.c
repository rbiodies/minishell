/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:50:23 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/15 18:41:19 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*k;
	unsigned char	ch;

	i = 0;
	k = (unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (*k == ch)
			return (k);
		k++;
		i++;
	}
	return ((void *)0);
}
