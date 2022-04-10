/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:36:10 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/25 15:44:41 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *buffer, size_t new_size)
{
	char	*new_buffer;
	size_t	old_size;

	if (buffer == 0)
		return (malloc(new_size));
	old_size = sizeof(buffer);
	if (new_size <= old_size)
		return (buffer);
	new_buffer = malloc(new_size);
	ft_memcpy(new_buffer, buffer, old_size);
	free(buffer);
	return (new_buffer);
}
