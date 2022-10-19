# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 12:47:27 by lorampon          #+#    #+#              #
#    Updated: 2022/10/19 13:12:28 by lorampon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRCS = \
				main.c\
				misc.c\
				init.c \
				exec.c

OBJS_NAME = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJ_DIR),$(OBJS_NAME))

OBJ_DIR = objs/
SRC_DIR = srcs/

CC = gcc

FLAGS = -Wall -Wextra -Werror #-fsanitize=thread


RM = rm -rf

all: $(OBJ_DIR) $(NAME)
	printf "Cest compile"

$(NAME) : $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	echo "##### so_long compiling finished! #####"	

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/philo.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJ_DIR)
	echo "##### Removed object files #####"

fclean: clean
	$(RM) $(NAME)
	echo "##### Removed binary files #####"

re : fclean all

git: fclean
	git add *
	git add -u
	git commit
	
.PHONY: all clean fclean leaks re

.SILENT: