/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:50:34 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/22 09:09:55 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("'", 2);
	return (1);
}

/*
a|||a
a&&&a
*/

static int	ft_three_pipe_after_text_error(char *line)
{
	int	i;

	i = 0;
	while (line[i + 3])
	{
		if (line[i] != '|' && line[i + 1] == '|' \
		&& line[i + 2] == '|' && line[i + 3] == '|' && line[i + 4] != '|')
			return (ft_syntax_error("|"));
		i++;
	}
	i = 0;
	while (line[i + 3])
	{
		if (line[i] != '&' && line[i + 1] == '&' \
		&& line[i + 2] == '&' && line[i + 3] == '&' && line[i + 4] != '&')
			return (ft_syntax_error("&"));
		i++;
	}
	return (0);
}

/*
>>>>
>>>
<<<<<<
<<<<<
<<<<
*/

static int	ft_redirect_error(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>' \
	&& line[i + 2] == '>' && line[i + 3] == '>')
		return (ft_syntax_error(">>"));
	if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
		return (ft_syntax_error(">"));
	if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<' \
	&& line[i + 3] == '<' && line[i + 4] == '<' && line[i + 5] == '<')
		return (ft_syntax_error("<<<"));
	if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<' \
	&& line[i + 3] == '<' && line[i + 4] == '<')
		return (ft_syntax_error("<<"));
	if (line[i] == '<' && line[i + 1] == '<' \
	&& line[i + 2] == '<' && line[i + 3] == '<')
		return (ft_syntax_error("<"));
	return (0);
}

/*
;;
"a|a"
||
"a&a"
&&
&a
*/

static int	ft_semicolon_and_pipe_error(char *line, int i)
{
	if (line[i] == ';' && line[i + 1] == ';')
		return (ft_syntax_error(";;"));
	if (line[i] != '|' && line[i + 1] == '|' && line[i + 3] != '|')
		return (2);
	if (line[i] == '|' && line[i + 1] == '|')
		return (ft_syntax_error("||"));
	if (line[i] != '&' && line[i + 1] == '&' && line[i + 3] != '&')
		return (2);
	if (line[i] == '&' && line[i + 1] == '&')
		return (ft_syntax_error("&&"));
	if (line[i] == '&' && line[i + 1] != '&')
		return (ft_syntax_error("&"));
	return (0);
}

// error of the line with semicolon, &, pipe and redirects

int	ft_line_error(char *line, t_his **history)
{
	int	i;

	if (ft_three_pipe_after_text_error(line) == 1)
	{
		free((*history)->his);
		(*history)->his = ft_strdup("258");
		return (1);
	}
	i = 0;
	while (line[i])
	{
		if (ft_semicolon_and_pipe_error(line, i) == 1 \
		|| ft_redirect_error(line, i) == 1)
		{
			free((*history)->his);
			(*history)->his = ft_strdup("258");
			return (1);
		}
		if (ft_semicolon_and_pipe_error(line, i) == 2)
			return (0);
		i++;
	}
	return (0);
}
