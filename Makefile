# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 18:29:55 by jvacaris          #+#    #+#              #
#    Updated: 2022/02/10 23:09:42 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	mandatory/philosophers.c			\
			mandatory/threads.c				\
			mandatory/utils.c					\
			mandatory/printer.c

OBJS = ${SRCS:.c=.o}

PATH_INCLUDES = ./includes/
PATH_LIBFT = ./libft/
PATH_MANDATORY = ./mandatory/

NAME = philo
LIBFT = libft.a
CC = @gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

all:		${NAME}
${NAME}:	${LIBFT} ${OBJS}
			@echo "\033[0;33mCompilation started\033[0m"
			${CC} ${CFLAGS} ${PATH_LIBFT}${LIBFT} ${OBJS} -I ${PATH_INCLUDES} -o ${NAME}
			@echo "\033[1;32m${NAME}\033[0;32m was successfully compiled!\033[0m"
${LIBFT}:	
			@make -C ${PATH_LIBFT}
clean:
	@echo "\033[0;34mCleaning started\033[0m"
	@${RM} ${OBJS}
	@make clean -C ${PATH_LIBFT}
	@echo "\033[0;36mCleaning done\033[0m"
fclean:		clean
	@${RM} ${NAME} libft/${LIBFT}
	@echo "\033[0;36m(executables \033[1;36m${NAME}\033[0;36m and \033[1;36m${LIBFT}\033[0;36m were also removed)\033[0m"
re:		fclean all
.PHONY: all clean fclean re