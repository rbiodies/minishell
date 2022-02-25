/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 12:01:21 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/12 12:11:06 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	int	i;

	i = 0;
	while (len != 0)
	{
		len--;
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
