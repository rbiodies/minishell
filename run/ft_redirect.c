/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:11:13 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/24 14:48:26 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_file(void)
{
	int	file;

	file = open("../pipe_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		perror("Open of File failed");
		return (-1);
	}
	return (file);
}

/*
cat << stop
->
cat ../pipe_file << stop
*/

int	ft_heredoc(t_list *temp, t_his **history)
{
	int		file;
	int		status;
	char	*line;

	file = ft_heredoc_file();
	if (file == -1)
		return (-1);
	temp->tokens[1] = ft_strdup("../pipe_file");
	status = 1;
	while (status > 0)
	{
		ft_putstr_fd("> ", 1);
		status = get_next_line(STDIN, &line);
		if (ft_strcmp(line, temp->next->tokens[0]) == 0)
			break ;
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	temp->tokens[2] = NULL;
	if (temp->tokens[0] != NULL)
		ft_run(temp, history);
	return (1);
}

/*
> F1 || > F1 > F2 || > F1 echo lol || < F1
<< stop
<< "f1"
*/

int	ft_redirect(t_list *temp, t_his **history)
{
	if (temp->tokens[0] == NULL && (temp->type == TYPE_TRUNC \
	|| temp->type == TYPE_APPEND || temp->type == TYPE_INPUT))
		return (ft_file_after_redirect(temp));
	else if (temp->tokens[0] == NULL \
	&& temp->type == TYPE_HEREDOC && temp->next)
		return (ft_heredoc(temp, history));
	else if (temp->prev && temp->prev->type == TYPE_HEREDOC)
		return (1);
	return (0);
}
