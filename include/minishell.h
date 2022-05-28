/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:32:23 by rbiodies          #+#    #+#             */
/*   Updated: 2022/04/10 11:13:11 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*****LIBRARIES*****/

# include "../libft/inc/libft.h"
# include <stdio.h>				//	printf()
# include <fcntl.h>				//	O_RDONLY
# include <sys/stat.h>			//	struct stat	f, lstat(), st_mode, S_IFDIR
# include <readline/readline.h>	//	readline()
# include <readline/history.h>	//	add_history()

/*****STRUCTURE*****/

typedef struct s_his
{
	char			*his;
	struct s_his	*next;
}	t_his;

/*****MACROS*****/

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define TYPE_END		3	//	!argv
# define TYPE_PIPE		4	//	|
# define TYPE_BREAK		5	//	;
# define TYPE_TRUNC		6	//	>
# define TYPE_APPEND	7	//	>>
# define TYPE_INPUT		8	//	<
# define TYPE_HEREDOC	9	//	<<
# define TYPE_OR		10	//	||
# define TYPE_AND		11	//	&&

/*****GLOBAL_VARIABLE*****/

char	**g_envp;

/*****FUNCTIONS*****/

/*****minishell*****/
void	ft_signal(void);
int		ft_add_history(char *line, t_his **history);
void	ft_input_eof(char **line, t_his	**history);
int		ft_line_error(char *line, t_his **history);
void	ft_parser(t_list **list, char **line, t_his **history);
int		ft_executor(t_list **list, t_his **history);
void	ft_free(t_his **history);
/*****ft_signal*****/
void	ft_hisclear(t_his **lst);
/*****ft_parser*****/
void	ft_lexer_exit(t_list **list, t_list **new, char *line, t_his **history);
void	ft_dollar(t_list **list, t_list *new, char *line, t_his **history);
void	ft_quotes(t_list **list, t_list *new, char *line, t_his **history);
char	**ft_split_minishell(char *s, char c);
/*****ft_split_minishell*****/
int		count_letter(char *s, char c, int i);
char	*handler_quote(char *s, char c);
/*****ft_lexer_quotes*****/
char	*ft_check_quotes(char *s);
/*****ft_executor*****/
int		ft_check_arguments(t_list *temp);
int		ft_syntax_error(char *error);
int		ft_check_our_cmd(char *token);
int		ft_run_our_cmd(t_list *temp, t_his **history);
int		ft_redirect(t_list *temp, t_his **history);
int		ft_get_path(t_list *temp, t_his **history);
void	ft_change_dir(char *path, int print_path, t_his **history);
void	ft_lstfree(t_list **list);
/*****ft_redirect*****/
int		ft_file_after_redirect(t_list *temp);
/*****ft_file_after_redirect*****/
void	ft_run(t_list *temp, t_his **history);
/*****ft_our_cmd*****/
int		ft_echo(t_list *temp);
int		ft_cd(char *token, t_his **history);
int		ft_export(char **token);
int		ft_unset(char **token);
int		ft_history_output(t_his **history);
int		ft_exit(t_list *temp, t_his **history);
/*****ft_export*****/
int		ft_strcmp_exp(char *s1, char *s2);
int		valid_export1(char *str, char **s);
int		valid_export2(char *str);
char	**error(char **arr);
void	add_quote(char **str);
void	ft_putarr_export(char **str);
int		quotes_handler(char **token);
int		quotes_handler2(char **token, int one, int two);
/*****ft_get_path*****/
int		ft_run_cmd(t_list *temp, t_his **history);
/*****ft_run_cmd*****/
void	ft_proc_signal_handler(int signum);
void	ft_cmd_and_pipe(t_list *temp, t_his **history);
/*****ft_child*****/
void	ft_file_after_cmd_and_redirect(t_list *temp, t_his **history);
void	ft_file_after_cmd_and_redirect_input(t_list *temp, t_his **history);
int		ft_heredoc(t_list *temp, t_his **history);
/*****ft_dollar_count*****/
int		ft_39(char *s, int *i, int count);
int		ft_34(char *s, int *i, int *flag, t_his *history);
int		ft_strlen_dollar(char *s);
/*****ft_fill*****/
char	*ft_create_str1(int count, char **s);
void	ft_move(int *j, char **s, char **new);
/*****ft_count*****/
int		ft_len_var(char *s, int *i, int *flag, t_his *history);
/*****ft_dollar*****/
int		ft_check_dollar(char *s, int *flag, t_his *history, int count);
void	fill_39(int *j, char **s, char **new);
void	fill_numb(char **new, char *numb, int *j, char **s);
int		fill_var(int *j, char **s, char **new);
int		fill_34(int *j, char **s, char **new, t_his *history);
/*****ft_lstadd_back*****/
void	ft_lstadd_back(t_list **lst, t_list *new);
/*****ft_lstfree*****/
void	ft_lstfree(t_list **list);

#endif