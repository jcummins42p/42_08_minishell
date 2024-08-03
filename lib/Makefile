# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2024/08/03 19:09:48 by akretov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER_DIR = include
CC = cc
CFLAGS = -g -Werror -Wextra -Wall -pedantic -fPIE -I$(HEADER_DIR)

SRC_DIR = mandatory
BSRC_DIR = bonus
PF_DIR = ft_printf
GNL_DIR = get_next_line

O_DIR = obj
BO_DIR = obj_bonus
PFO_DIR = obj_pf
GNLO_DIR = obj_gnl

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(O_DIR)/%.o)
B_SRCS = $(shell find $(BSRC_DIR) -name '*.c')
B_OBJS = $(B_SRCS:$(BSRC_DIR)/%.c=$(BO_DIR)/%.o)
PF_SRCS = $(shell find $(PF_DIR) -name '*.c')
PF_OBJS = $(PF_SRCS:$(PF_DIR)/%.c=$(PFO_DIR)/%.o)
GNL_SRCS = $(shell find $(GNL_DIR) -name '*.c')
GNL_OBJS = $(GNL_SRCS:$(GNL_DIR)/%.c=$(GNLO_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(B_OBJS) $(PF_OBJS) $(GNL_OBJS)
	@echo "✅ Making libft mandatory and adding to libft.a"
	@ar -r $@ $?
	@ranlib $(NAME)

bonus: $(B_OBJS)
	@echo "✅ Making libft bonus and adding to libft.a"
	@ar -r $(NAME) $^
	@ranlib $(NAME)

printf:	$(PF_OBJS)
	@echo "✅ Adding printf to library"
	@ar -r $(NAME) $^
	@ranlib $(NAME)

gnl:	$(GNL_OBJS)
	@echo "✅ Adding get_next_line to library"
	@ar -r $(NAME) $^
	@ranlib $(NAME)

$(O_DIR)/%.o:	$(SRC_DIR)/%.c
	@echo "✅ Compiled object file $@ from source file $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BO_DIR)/%.o: $(BSRC_DIR)/%.c
	@echo "✅ Compiled object file $@ from source file $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(PFO_DIR)/%.o: $(PF_DIR)/%.c
	@echo "✅ Compiled object file $@ from source file $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(GNLO_DIR)/%.o: $(GNL_DIR)/%.c
	@echo "✅ Compiled object file $@ from source file $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "💥 Removing all object files"
	@rm -rf $(O_DIR) $(BO_DIR) $(PFO_DIR) $(GNLO_DIR)
	@rm -rf *.so

fclean: clean
	@echo "💥 Removing all object files and library"
	@rm -rf $(NAME)
	@rm -rf *.out

re:	fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BSRC)
	gcc -nostartfiles -shared -fPIC -o libft.so $(OBJS) $(BOBS)

.PHONY: all clean fclean re bonus printf gnl
