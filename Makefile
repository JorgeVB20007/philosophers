# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 18:29:55 by jvacaris          #+#    #+#              #
#    Updated: 2022/02/02 19:18:11 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	philosophers.c			\
			threads.c				\
			utils.c

OBJS = ${SRCS:.c=.o}

PATH_INCLUDES = ./includes/
PATH_LIBFT = ./libft/
PATH_MANDATORY = ./mandatory/

NAME = philosophers
LIBFT = libft.a
CC = @gcc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra #-lpthread
OBJS_PTH = $(addprefix ./obj/, $(OBJS))
SRCS_PTH = $(addprefix ./mandatory/, $(SRCS))

all:		obj ${NAME}
${NAME}:	${LIBFT} ${OBJS_PTH} 
	@echo "\033[0;33mStarting compilation\033[0m"
	${CC} ${CFLAGS} ${PATH_LIBFT}${LIBFT} ${OBJS_PTH} -I ${PATH_INCLUDES} -o ${NAME}
	@echo "\033[1;32m>\033[1;36m" ${NAME} "\033[0;32msuccessfully compiled!\033[0m"
${LIBFT}:	
	@make -C ${PATH_LIBFT}
obj:	
	@mkdir -p ./obj/
clean:
	@echo "\033[0;33mCleaning some stuff over here!\033[0m"
	@${RM} ./obj/
	@make clean -C ${PATH_LIBFT}
	@echo "\033[0;32mCleaning done!\033[0m"
fclean:		clean
	@${RM} ${NAME} libft/${LIBFT}
re:		fclean all
.PHONY: all clean fclean re