# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2024/08/01 17:12:31 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEAD_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CC = cc
CFLAGS = -g -Werror -Wextra -Wall -pedantic -I$(HEAD_DIR)
LIB = libft.a
LIB_DIR = lib
LIB_PATH = $(LIB_DIR)/$(LIB)

SRCS = $(shell find $(SRC_DIR) -name '*.c')
HEADS = $(shell find $(HEAD_DIR) -name '*.h')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH) $(MLX_PATH)
	@$(CC) $(CFLAGS) -L$(LIB_DIR) -lreadline $^ -o $@
	@echo "✅ Linking object files into executable $@"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I/usr/include -I$(HEAD_DIR) -c $< -o $@
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
	@(cd $(LIB_DIR) && make fclean)

re:	fclean all

.PHONY: all clean fclean re
