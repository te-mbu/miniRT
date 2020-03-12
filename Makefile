SRCNAME	= 	main.c	\
			

SRCS	= ${SRCNAME}

OBJS	= ${SRCS:.c=.o}

NAME	= miniRT

CC	= gcc
RM	= rm -f

CFLAGS = -Wall -Wextra -Werror -I.

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C mlx
			${CC} -o ${NAME} ${OBJS} -Lmlx -lmlx -framework OpenGL -framework AppKit
			
all: 		${NAME}

clean:
			make -C mlx clean
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:		fclean all

c:		all clean

.PHONY:		clean fclean re all bonus