# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 18:29:55 by jvacaris          #+#    #+#              #
#    Updated: 2022/03/02 21:04:25 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= philo
GCC		= gcc
FLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address

INCLUDES_FILES =	philosophers.h

MAND_FILES	= 	parent.c			\
				parent_creators.c	\
				parent_utils.c		\
				philoroutine.c		\
				philosophers.c		\
				not_libft.c			\
				utils_one.c			\
				utils_two.c

OBJ_FILES	= $(MAND_FILES:.c=.o)

MAND_DIR = ./mandatory/
OBJ_DIR = ./objects/
INC_DIR = ./includes/

MAND = $(addprefix $(MAND_DIR), $(MAND_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))

all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(MAND_DIR)%.c $(INCLUDES)
	@$(GCC) $(FLAGS) -pthread -I $(INC_DIR)  -o $@ -c $<

$(NAME): $(OBJ)
	@echo "\033[0;33mCompilation started\033[0;31m"
	@$(GCC) $(OBJ) $(FLAGS) $(LNK) -lm -o $(NAME)
	@echo "\033[0;32mCompilation successful. File \033[1;32m$(NAME)\033[0;32m generated!\033[0;37m"

clean:
	@echo "\033[0;34mCleaning started\033[0m"
	@rm -Rf $(OBJ_DIR)
	@echo "\033[0;36mCleaning done. All objects were removed.\033[0m"

fclean:		clean
	@rm -f $(NAME)
	@echo "\033[0;36mExecutable \033[1;36m$(NAME)\033[0;36m removed!\033[0m"

re:			fclean all

.PHONY:		all clean fclean re