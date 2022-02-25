
NAME		=	minishell

LIB_PATH	=	libft/

LIB			=	${LIB_PATH}libft.a

SRCS_LIB	=	new_libft/ft_arrlen.c		new_libft/ft_strfree.c		new_libft/ft_realloc.c \
				new_libft/ft_lstfree.c		new_libft/ft_strndup.c		new_libft/ft_putnstr_fd.c \
				new_libft/ft_strreplace.c	new_libft/ft_strjoinch.c	new_libft/ft_strjoin_divider.c \
				new_libft/ft_putarr.c

SRCS		=	minishell.c					ft_signal.c					get_next_line.c \
				ft_line_error.c				ft_parser.c					ft_lexer_quotes.c \
				ft_executor.c				ft_check_arguments.c		ft_redirect.c \
				ft_file_after_redirect.c	ft_our_cmd.c				ft_echo.c \
				ft_cd.c						ft_exit.c					ft_get_path.c \
				ft_run_cmd.c				ft_child.c					ft_child_input.c \
				ft_history_lst.c			ft_unset.c					ft_export_utils.c \
				ft_export.c					ft_split_minishell.c		ft_split_utils.c \
				ft_quotes.c					ft_dollar.c 				ft_dollar_count.c \
				ft_fill.c					ft_count.c

HEADER		=	minishell.h
OBJDIR		=	objects
OBJS_LIB	=	${SRCS_LIB:%.c=${OBJDIR}/%.o}

OBJS		=	${SRCS:%.c=${OBJDIR}/%.o}

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

READLINE	=	-lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1.1/lib/

RM			=	rm -rf

.PHONY		: 	all clean fclean re subsystem readline

all			:	subsystem ${NAME}

subsystem	:	
				make -C ${LIB_PATH} all
				@printf "\033[0;33m💬 Libft make complete !✅\033[0m\n"

${NAME}		:	${OBJS_LIB} ${OBJS}
				${CC} ${CFLAGS} -I${HEADER} ${READLINE} ${OBJS_LIB} ${OBJS} ${LIB} -o ${NAME}
				@printf "\033[0;32m💬 Create file '"${NAME}"' !✅\033[0m\n"

${OBJDIR}	:
				mkdir -p ${OBJDIR}
				mkdir -p ${OBJDIR}/new_libft

${OBJDIR}/%.o: %.c | ${OBJDIR}
				${CC} ${CFLAGS} -I${HEADER} -I/Users/${USER}/.brew/Cellar/readline/8.1.1/include -c $< -o $@

readline	:
				brew install readline

clean		:	
				make -C ${LIB_PATH} clean
				${RM} ${OBJDIR}
				@printf "\033[0;34m👻 Files *.o clean ! 🗑️\033[0m\n"

fclean		:	clean
				${RM} ${NAME} ${LIB}
				@printf "\033[0;32m🍀 All clean ! 🗑️\033[0m\n"

re			: 	fclean all