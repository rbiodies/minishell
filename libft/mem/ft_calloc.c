/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:53:07 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/14 14:34:35 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*buffer;

	i = 0;
	buffer = (void *) malloc(count * size);
	if (buffer == NULL)
		return (0);
	while (count * size > i)
	{
		((char *)buffer)[i] = '\0';
		i++;
	}
	return (buffer);
}
