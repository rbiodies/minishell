/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:34:32 by bjeana            #+#    #+#             */
/*   Updated: 2022/02/24 10:46:52 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_str1(int count, char **s)
{
	int		k;
	char	*str;

	k = 0;
	(*s)++;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (NULL);
	while (k < count)
	{
		str[k] = **s;
		(*s)++;
		k++;
	}
	str[k] = '\0';
	return (str);
}

void	ft_move(int *j, char **s, char **new)
{
	char	*str;

	str = *s;
	(*new)[*j] = *str;
	*j = *j + 1;
	str++;
	*s = str;
}

static char	*ft_changing(char *s, int count, t_his *history)
{
	int		j;
	int		ret;
	char	*new;

	j = 0;
	ret = 0;
	new = ft_calloc(count + 1, sizeof(char));
	while (new != NULL && *s != '\0')
	{
		if (*s == 39)
			fill_39(&j, &s, &new);
		else if (*s == '$' && *(s + 1) == '?')
			fill_numb(&new, history->his, &j, &s);
		else if (*s == '$')
			ret = fill_var(&j, &s, &new);
		else if (*s == 34)
			ret = fill_34(&j, &s, &new, history);
		else
			ft_move(&j, &s, &new);
		if (ret == -1)
			return (NULL);
	}
	return (new);
}

void	ft_dollar(t_list **list, t_list *new, char *line, t_his **history)
{
	int		i;
	int		flag;
	int		count;
	char	*temp;

	i = -1;
	while (new->tokens[++i] != NULL)
	{
		flag = 0;
		count = ft_check_dollar(new->tokens[i], &flag, *history, 0);
		if (count == -1)
			ft_lexer_exit(list, &new, line, history);
		if ((*list) != NULL && ((*list)->type == TYPE_TRUNC \
		|| (*list)->type == TYPE_APPEND || (*list)->type == TYPE_INPUT \
		|| (*list)->type == TYPE_HEREDOC) && flag == 2)
			return ;
		if (flag > 0)
		{
			temp = new->tokens[i];
			new->tokens[i] = ft_changing(new->tokens[i], count, *history);
			free(temp);
		}
		if (new->tokens[i] == NULL)
			ft_lexer_exit(list, &new, line, history);
	}
}
