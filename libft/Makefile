
NAME	= 	libft.a

SRCS	= 	ascii/ft_isalpha.c		ascii/ft_isdigit.c		ascii/ft_isalnum.c\
			ascii/ft_isascii.c		ascii/ft_isprint.c		ascii/ft_toupper.c\
			ascii/ft_tolower.c\
			\
			math/ft_atoi.c 			math/ft_itoa.c\
			\
			mem/ft_memset.c			mem/ft_bzero.c			mem/ft_memcpy.c\
		   	mem/ft_memmove.c		mem/ft_memcmp.c			mem/ft_calloc.c\
			mem/ft_memchr.c\
			\
			put/ft_putchar_fd.c		put/ft_putstr_fd.c		put/ft_putendl_fd.c\
			put/ft_putnbr_fd.c\
			\
			str/ft_strdup.c			str/ft_substr.c			str/ft_strnstr.c\
			str/ft_strlen.c			str/ft_strlcpy.c		str/ft_strlcat.c\
		   	str/ft_strchr.c			str/ft_strrchr.c		str/ft_strncmp.c\
		   	str/ft_strjoin.c		str/ft_strtrim.c		str/ft_split.c\
		   	str/ft_strmapi.c		str/ft_striteri.c		str/ft_strcmp.c\
			\
			lst/ft_lstadd_back.c

SRCS_B	= 	lst/ft_lstnew.c			lst/ft_lstadd_front.c	lst/ft_lstsize.c\
			lst/ft_lstlast.c		lst/ft_lstadd_back.c	lst/ft_lstdelone.c\
		   	lst/ft_lstclear.c		lst/ft_lstiter.c		lst/ft_lstmap.c\
			lst/ft_lstdelfirst.c	lst/ft_lstclear_my.c

HEADER	=	-I inc/
OBJ		=	${SRCS:%.c=%.o}
OBJ_B	=	${SRCS_B:%.c=%.o}

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror ${HEADER}

.PHONY:		all clean fclean re bonus

all:		${NAME}

${NAME}	:	${OBJ}
			ar rcs ${NAME} $?

%.o : %.c	${HEADER}
			${CC} ${CFALGS} -c $< -o $@

bonus	:
			make OBJ="${OBJ_B}" all

clean	:
			${RM} ${OBJ} ${OBJ_B}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all
