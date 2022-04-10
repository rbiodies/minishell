/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:07:08 by rbiodies          #+#    #+#             */
/*   Updated: 2022/03/30 12:12:54 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*buffer;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	buffer = (char *)malloc(i + 1);
	if (buffer == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		buffer[i] = s1[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
