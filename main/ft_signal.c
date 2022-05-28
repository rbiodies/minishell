/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:43:56 by rbiodies          #+#    #+#             */
/*   Updated: 2022/04/10 11:02:03 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ctrl-C in fork

void	ft_proc_signal_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_free(t_his **history)
{
	ft_hisclear(history);
	ft_arrfree(g_envp);
}

// user pressed ctrl-D

void	ft_input_eof(char **line, t_his **history)
{
	if (*line != NULL)
		free (*line);
	ft_putendl_fd("exit", STDERR);
	ft_free(history);
	exit(EXIT_SUCCESS);
}

/*
53 save the current line contents
54 set the line to blank
*/

static void	ft_signal_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
Ctrl-C
ignore Ctrl-Z Ctrl-\ signals
*/

void	ft_signal(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
