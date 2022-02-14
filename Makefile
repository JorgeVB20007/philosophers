# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 18:29:55 by jvacaris          #+#    #+#              #
#    Updated: 2022/02/14 21:32:27 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= philo
GCC		= gcc
FLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address

INCLUDES_FILES =	philosophers.h

MAND_FILES	= 	parent.c		\
				philosophers.c	\
				utils.c

OBJ_FILES	= $(MAND_FILES:.c=.o)

MAND_DIR = ./mandatory/
OBJ_DIR = ./objects/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

MAND = $(addprefix $(MAND_DIR), $(MAND_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

LNK  = -L $(LIBFT_DIR) -lft

all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(MAND_DIR)%.c $(INCLUDES)
	@$(GCC) $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@echo "\033[0;33mCompilation started\033[0;31m"
	@$(GCC) $(OBJ) $(FLAGS) $(LNK) -lm -o $(NAME)
	@echo "\033[0;32mCompilation successful. File \033[1;32m$(NAME)\033[0;32m generated!\033[0;37m"

clean:
	@echo "\033[0;34mCleaning started\033[0m"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[0;36mCleaning done. All objects were removed.\033[0m"

fclean:		clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[0;36mExecutable \033[1;36m$(NAME)\033[0;36m removed!\033[0m"

re:			fclean all

.PHONY:		all clean fclean re