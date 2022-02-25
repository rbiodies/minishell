/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:55:34 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/15 15:02:42 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const s1, char const *set)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (s1 == set[j])
			return (1);
		j++;
	}
	return (0);
}

static char	*ft_arr(char const *s1, int start, int end)
{
	int		k;
	char	*arr;

	k = 0;
	arr = (char *)malloc(sizeof(char) * (end - start + 1 + 1));
	if (arr == (char *)(void *)0)
		return (NULL);
	while (start <= end)
	{
		arr[k] = s1[start];
		start++;
		k++;
	}
	arr[k] = '\0';
	return (arr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*arr;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0' && ft_isset(s1[i], set) == 1)
		i++;
	start = i;
	while (s1[i] != '\0')
		i++;
	i--;
	while (i >= 0 && ft_isset(s1[i], set) == 1)
		i--;
	end = i;
	if (end == -1)
		end = start - 1;
	arr = ft_arr(s1, start, end);
	return (arr);
}
