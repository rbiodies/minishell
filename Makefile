
NAME		=	minishell

LIB_PATH	=	libft/

LIB			=	${LIB_PATH}libft.a

SRCS		=	${wildcard *.c}

HEADER		=	minishell.h
OBJDIR		=	objects

OBJS		=	${SRCS:%.c=${OBJDIR}/%.o}

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
				@${CC} ${CFLAGS} -I${HEADER} ${READLINE} ${OBJS} ${LIB} -o ${NAME}
				@printf "\033[0;32m💬 File '${NAME}' is created !  ✅\033[0m\n"

${OBJDIR}	:
				@mkdir -p ${OBJDIR}

${OBJDIR}/%.o: %.c | ${OBJDIR}
				@${CC} ${CFLAGS} -I${HEADER} -I/Users/${USER}/.brew/Cellar/readline/8.1.1/include -c $< -o $@

readline	:
				brew install readline

clean		:	
				@make -C ${LIB_PATH} clean
				@${RM} ${OBJDIR}
				@printf "\033[0;34m👻 Files '${OBJS}' are deleted ! 🗑️\033[0m\n"

fclean		:	clean
				@${RM} ${NAME} ${LIB}
				@printf "\033[0;31m💬 File '${NAME}' is deleted ! 🗑️\033[0m\n"

re			: 	fclean all