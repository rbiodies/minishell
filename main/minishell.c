/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:49:09 by rbiodies          #+#    #+#             */
/*   Updated: 2022/04/10 11:01:45 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SHLVL=2

static void	ft_check_shlvl(void)
{
	int		i;
	char	*number;

	i = 0;
	while (g_envp && g_envp[i] && ft_strncmp("SHLVL=", g_envp[i], 6))
		i++;
	if (g_envp[i] == NULL)
		return ;
	number = ft_itoa(ft_atoi(ft_strrchr(g_envp[i], '=') + 1) + 1);
	free(g_envp[i]);
	g_envp[i] = ft_strjoin("SHLVL=", number);
	free(number);
	if (!g_envp[i])
	{
		ft_arrfree(g_envp);
		exit(EXIT_FAILURE);
	}
}

static void	ft_init_env(int argc, char **argv, char **envp)
{
	int	i;

	(void)argc;
	(void)argv;
	g_envp = (char **)malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	if (g_envp == NULL)
		exit(EXIT_FAILURE);
	ft_bzero(g_envp, sizeof(char *) * (ft_arrlen(envp) + 1));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("OLDPWD=", envp[i], 7) == 0)
		{
			g_envp[i] = ft_strdup("OLDPWD=");
			continue ;
		}
		g_envp[i] = ft_strdup(envp[i]);
		if (!g_envp[i])
		{
			ft_arrfree(g_envp);
			exit(EXIT_FAILURE);
		}
	}
	g_envp[i] = NULL;
	ft_check_shlvl();
}

// ~ + current path without HOME path

static char	*ft_parse_home_path(char *pwd)
{
	char	*home_path;
	char	*path;

	if (!pwd)
		return (NULL);
	home_path = getenv("HOME");
	if (ft_strncmp(home_path, pwd, ft_strlen(home_path)) != 0)
		return (ft_strdup(pwd));
	path = ft_strjoin("~", pwd + ft_strlen(home_path));
	return (path);
}

// set promt and read line

static char	*ft_display_message(void)
{
	char	*pwd;
	char	buff[4096 + 1];
	char	*parse_pwd;
	char	*prompt;
	char	*line;

	pwd = getcwd(buff, 4096);
	parse_pwd = ft_parse_home_path(pwd);
	prompt = ft_strjoin(parse_pwd, "\033[0;36m\033[1m$\033[0m ");
	free(parse_pwd);
	line = readline(prompt);
	free(prompt);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*line;
	t_list	*list;
	t_his	*history;

	ft_init_env(argc, argv, envp);
	ft_signal();
	status = ft_add_history("0", &history);
	while (status != -1)
	{
		line = ft_display_message();
		if (line && (ft_strlen(line) == 0 || ft_line_error(line, &history)))
		{
			free(line);
			continue ;
		}
		if (line == NULL || ft_add_history(line, &history) == -1)
			ft_input_eof(&line, &history);
		add_history(line);
		ft_parser(&list, &line, &history);
		status = ft_executor(&list, &history);
	}
	status = ft_atoi(history->his);
	ft_free(&history);
	return (status);
}
