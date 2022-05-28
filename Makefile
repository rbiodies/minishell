
NAME		=	minishell

LIB_PATH	=	libft/

LIB			=	${LIB_PATH}libft.a

SRCS		=	${wildcard main/*.c parser/*.c dollar/*.c executor/*.c commands/*.c run/*.c}

HEADER		=	-I include/
OBJS		=	${SRCS:%.c=%.o}

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

READLINE	=	-lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1.1/lib/

RM			=	rm -rf

.PHONY		: 	all clean fclean re subsystem readline

all			:	subsystem ${NAME}

subsystem	:	
				@make -C ${LIB_PATH} all
				@printf "\033[0;33m🍀 File '${LIB}' is done ! ✅\033[0m\n"

${NAME}		:	${OBJS_LIB} ${OBJS}
				@${CC} ${CFLAGS} ${HEADER} ${READLINE} ${OBJS} ${LIB} -o ${NAME}
				@printf "\033[0;32m💬 File '${NAME}' is created !  ✅\033[0m\n"

${OBJDIR}	:
				@mkdir -p ${OBJDIR}

%.o			:	%.c
				@${CC} ${CFLAGS} ${HEADER} -I/Users/${USER}/.brew/Cellar/readline/8.1.1/include -c $< -o $@

readline	:
				brew install readline

clean		:	
				@make -C ${LIB_PATH} clean
				@${RM} ${OBJS}
				@printf "\033[0;34m👻 Files '${OBJS}' are deleted ! 🗑️\033[0m\n"

fclean		:	clean
				@${RM} ${NAME} ${LIB}
				@printf "\033[0;31m💬 File '${NAME}' is deleted ! 🗑️\033[0m\n"

re			: 	fclean all