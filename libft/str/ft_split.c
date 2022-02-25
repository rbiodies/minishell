/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:42:54 by rbiodies          #+#    #+#             */
/*   Updated: 2021/10/15 12:34:34 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	ft_isspace(char ch, char c)
{
	if (ch == c)
		return (1);
	return (0);
}

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s, c) == 1)
			s++;
		if (*s && ft_isspace(*s, c) == 0)
		{
			count++;
			while (*s && ft_isspace(*s, c) == 0)
				s++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && ft_isspace(s[i], c) == 0)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == (char *)(void *)0)
		return (NULL);
	i = 0;
	while (s[i] && ft_isspace(s[i], c) == 0)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (arr == (char **)(void **)0)
		return (NULL);
	while (*s)
	{
		while (*s && ft_isspace(*s, c) == 1)
			s++;
		if (*s && ft_isspace(*s, c) == 0)
		{
			arr[i] = malloc_word(s, c);
			if (arr[i] == NULL)
				return (ft_malloc_error(arr));
			i++;
			while (*s && ft_isspace(*s, c) == 0)
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
