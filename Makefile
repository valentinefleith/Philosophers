# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 15:31:12 by vafleith          #+#    #+#              #
#    Updated: 2024/10/16 11:30:26 by vafleith         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -gdwarf-4
# CFLAGS += -Werror

INC = -Iinclude

SRC_DIR = src

SRCS = main.c print/print.c print/error_messages.c \
	   parse/parse.c parse/parse_utils.c parse/string_utils.c \
	   simulate/dinner_constructor.c simulate/dinner_destructor.c \
	   simulate/handle_time.c simulate/simulation.c
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
