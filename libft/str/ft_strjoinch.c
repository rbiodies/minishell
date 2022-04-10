/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:50:16 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/25 15:44:49 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinch(char *str, char ch)
{
	char	*new_str;
	size_t	i;

	if (!str || !ch)
		return (NULL);
	new_str = (char *)malloc(sizeof(new_str) * (ft_strlen(str) + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = ch;
	i++;
	new_str[i] = '\0';
	return (new_str);
}
