/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:00:12 by bjeana            #+#    #+#             */
/*   Updated: 2022/01/31 15:33:15 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	count_word(char *s, char c)
{
	int	word;

	word = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			word++;
			s = handler_quote(s, c);
		}
		else
			s++;
	}
	return (word);
}

static char	*create_word(char *s, char c)
{
	char	*arr;
	int		i;

	i = count_letter(s, c, -1);
	arr = (char *)malloc((i + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0' && s[i] != c)
	{
		arr[i] = s[i];
		if (s[i] == 34)
		{
			while (s[++i] != 34 && s[i] != '\0')
				arr[i] = s[i];
		}
		else if (s[i] == 39)
		{
			while (s[++i] != 39 && s[i] != '\0')
				arr[i] = s[i];
		}
		arr[i] = s[i];
	}
	arr[i] = '\0';
	return (arr);
}

static char	**ft_fill_arr(char *s, char c, char	**arr, int word)
{
	int	i;

	i = 0;
	while (i < word && *s != '\0')
	{
		if (*s != c)
		{
			arr[i] = create_word(s, c);
			if (arr[i] == NULL)
				return (ft_malloc_error(arr));
			s = handler_quote(s, c);
			i++;
		}
		s++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_minishell(char *s, char c)
{
	char	**arr;
	int		word;

	if (s == NULL)
		return (NULL);
	word = count_word(s, c);
	arr = (char **)malloc((word + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (ft_fill_arr(s, c, arr, word));
}
