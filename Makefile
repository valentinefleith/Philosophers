# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 15:31:12 by vafleith          #+#    #+#              #
#    Updated: 2024/10/14 18:00:02 by vafleith         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -g3
# CFLAGS += -Werror

INC = -Iinclude

SRC_DIR = src

SRCS = main.c print.c error_messages.c parse.c parse_utils.c general_utils.c \
	   philo_init.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR = build
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all
all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "philo ready."

.PHONY: clean
clean:
	@echo Cleaning up object files	
	@rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)

.PHONY: re
re: fclean all
