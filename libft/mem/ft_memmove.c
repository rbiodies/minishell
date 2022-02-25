/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:46:57 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/12 16:58:38 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	i = 0;
	if (dst == '\0' && src == '\0')
		return (((void *)0));
	if (dst < src)
	{
		while (len != 0)
		{	
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
			len--;
		}
	}
	else
	{
		i = len - 1;
		while (len != 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			len--;
			i--;
		}
	}
	return (dst);
}
