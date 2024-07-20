# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2024/07/20 15:46:53 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CC = cc
CFLAGS = -g -Werror -Wextra -Wall -pedantic -I$(HEADER_DIR)
LIB = libft.a
LIB_DIR = lib
LIB_PATH = $(LIB_DIR)/$(LIB)

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	@$(CC) $(CFLAGS) $^ -o $@ -L$(LIB_DIR) -lreadline
	@echo "✅ Linking object files into executable $@"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I/usr/include -I$(HEADER_DIR) -c $< -o $@
	@echo "✅ Complied object file $@ from source file $<"

$(LIB_PATH):
	@(cd $(LIB_DIR) && make)
	@echo "✅ Complied libft library"

clean:
	@echo "💥 Removing all object files"
	@rm -rf $(OBJ_DIR)
	@(cd $(LIB_DIR) && make clean)

fclean: clean
	@echo "💥 Removing all object files and executable"
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
