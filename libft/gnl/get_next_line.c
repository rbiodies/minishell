/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:07:14 by rbiodies          #+#    #+#             */
/*   Updated: 2022/02/01 10:53:30 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_newbackup(char *backup)
{
	int		i;
	char	*newbackup;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
	{
		free(backup);
		return (NULL);
	}
	newbackup = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!newbackup)
		return (NULL);
	ft_strlcpy(newbackup, backup + i + 1, ft_strlen(backup) - i + 1);
	free(backup);
	return (newbackup);
}

static int	make_line(char **line, char *backup)
{
	int		i;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	*line = malloc(sizeof(char *) * (i + 1));
	if (!*line)
		return (-1);
	ft_strlcpy(*line, backup, i + 1);
	if (*line[0] == '\0')
	{
		free(*line);
		return (-1);
	}
	return (1);
}

static char	*make_backup(int fd, char *backup, char *buffer)
{
	char	*tmp;
	int		bytes_was_read;
	int		flag;

	bytes_was_read = 1;
	flag = 0;
	while (flag == 0 && bytes_was_read != 0)
	{
		bytes_was_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_was_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_was_read] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(backup, buffer);
		free(tmp);
		if (ft_strchr(backup, '\n'))
			flag = 1;
	}
	free(buffer);
	return (backup);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*backup;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	backup = make_backup(fd, backup, buffer);
	if (!backup)
		return (-1);
	status = make_line(line, backup);
	backup = make_newbackup(backup);
	return (status);
}
