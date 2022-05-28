/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:32:31 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 14:11:19 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parser_quotes(char *line, int i, char quote)
{
	i++;
	while (line[i] != quote && line[i] != '\0')
		i++;
	return (i);
}

/*
34 - '
39 - "
*/

static int	ft_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 34)
			i = ft_parser_quotes(line, i, 34);
		else if (line[i] == 39)
			i = ft_parser_quotes(line, i, 39);
		else if (line[i] == '|' || line[i] == ';' \
		|| line[i] == '>' || line[i] == '<' || line[i] == '&')
		{
			if (i == 0)
				return (0);
			return (i);
		}
		i++;
	}
	return (i);
}

static int	ft_type(char *line)
{
	if (!*line)
		return (TYPE_END);
	else if (*line == '|' && *(line + 1) == '|')
		return (TYPE_OR);
	else if (*line == '|')
		return (TYPE_PIPE);
	else if (*line == ';')
		return (TYPE_BREAK);
	else if (*line == '>' && *(line + 1) == '>')
		return (TYPE_APPEND);
	else if (*line == '>')
		return (TYPE_TRUNC);
	else if (*line == '<' && *(line + 1) == '<')
		return (TYPE_HEREDOC);
	else if (*line == '<')
		return (TYPE_INPUT);
	else if (*line == '&' && *(line + 1) == '&')
		return (TYPE_AND);
	return (0);
}

static int	ft_lexer(t_list **list, t_list *new, char *line, t_his **history)
{
	int	i;

	i = 0;
	while (i < new->size)
	{
		new->argv[i] = line[i];
		i++;
	}
	new->argv[i] = '\0';
	new->tokens = ft_split_minishell(new->argv, ' ');
	if (!new->tokens)
		ft_lexer_exit(list, &new, line, history);
	ft_dollar(list, new, line, history);
	ft_quotes(list, new, line, history);
	new->prev = NULL;
	new->next = NULL;
	new->cmd_with_path = NULL;
	new->type = ft_type(&line[i]);
	if (new->type == TYPE_APPEND \
	|| new->type == TYPE_OR || new->type == TYPE_HEREDOC)
		i++;
	else if (new->type == TYPE_AND)
		i = ft_strlen(line);
	ft_lstadd_back(list, new);
	return (i);
}

void	ft_parser(t_list **list, char **line, t_his **history)
{
	char	*temp;
	int		i;
	t_list	*new;

	temp = *line;
	i = 0;
	while (i < (int)ft_strlen(temp))
	{
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
			ft_lexer_exit(list, &new, temp, history);
		new->size = ft_size(temp + i);
		new->argv = (char *)malloc((sizeof(char)) * (new->size + 1));
		if (!new->argv)
			ft_lexer_exit(list, &new, temp, history);
		i += ft_lexer(list, new, &temp[i], history);
		i++;
	}
	free(*line);
}
