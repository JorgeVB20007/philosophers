# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 18:29:55 by jvacaris          #+#    #+#              #
#    Updated: 2022/02/01 21:35:38 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	./mandatory/philosophers.c			\
			./mandatory/utils.c

OBJS = ${SRCS:.c=.o}

PATH_INCLUDES = ./includes/
PATH_LIBFT = ./libft/
PATH_MANDATORY = ./mandatory/

NAME = philosophers
LIBFT = libft.a
CC = @gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -lpthread

all:		${NAME}
${NAME}:	${LIBFT} ${OBJS} 
	@echo "\033[0;33mStarting compilation\033[0m"
	${CC} ${CFLAGS} ${PATH_LIBFT}${LIBFT} ${OBJS} -I ${PATH_INCLUDES} -o ${NAME}
	@echo "\033[1;32m>\033[1;36m" ${NAME} "\033[0;32msuccessfully compiled!\033[0m"
${LIBFT}:	
	@make -C ${PATH_LIBFT}
clean:
	@echo "\033[0;33mCleaning some stuff over here!\033[0m"
	@${RM} ${OBJS}
	@make clean -C ${PATH_LIBFT}
	@echo "\033[0;32mCleaning done!\033[0m"
fclean:		clean
	@${RM} ${NAME} libft/${LIBFT}
re:		fclean all
.PHONY: all clean fclean re