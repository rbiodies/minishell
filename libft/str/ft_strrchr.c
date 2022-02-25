/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:49:30 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/15 18:43:09 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*k;
	char		ch;

	k = (char *)s;
	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			k = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	s = k;
	if (*s == ch)
		return ((char *)s);
	return ((void *)0);
}
