# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 16:01:23 by maroy             #+#    #+#              #
#    Updated: 2023/11/21 16:46:12 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I./inc -std=c99 -O3

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS += -I$(LIBFT_DIR)/inc -L$(LIBFT_DIR) -lft

LIBFT	= ./libs/libft/libft.a
ifeq ($(shell uname), Linux)
	MLX		= ./libs/minilibx-linux/libmlx.a
else ifeq ($(shell uname), Darwin)
	MLX		= ./libs/minilibx-mac-osx/libmlx.a
else
	@echo "${RED}Error: MLX is not available on your system. 🚫${DEFAULT}"
endif

SRC_MAIN_DIR		= src
SRC_PARSING_DIR 	= 	$(SRC_MAIN_DIR)/parsing
SRC_GAME_DIR		=	$(SRC_MAIN_DIR)/game

SRCS_MAIN	=	main.c \
				debug.c

SRCS_PARSING =  valid.c \
				parsing.c \
				parsing_utils.c \

SRCS_GAME 	=	init.c

SRC_M = $(addprefix $(SRC_MAIN_DIR)/, $(SRCS_MAIN))
SRC_P = $(addprefix $(SRC_PARSING_DIR)/, $(SRCS_PARSING))
SRC_G = $(addprefix $(SRC_GAME_DIR)/, $(SRCS_GAME))

SRC		= $(SRC_M) $(SRC_P) $(SRC_G)


BIN     = $(patsubst $(SRC)/%.c,bin/%.o,$(SRC))

MK		= mkdir -p
RM		= rm -rf

bin/%.o: $(SRC)/%.c
	@$(MK) $(@D)
	@printf "\r${DARKGRAY}Compiling : $(@F) ... ${DEFAULT}\033[K"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(MLX) $(NAME)

debug: CFLAGS += -DDEBUG_MODE=1 -g3 -fsanitize=address
debug: re

$(LIBFT):
	@echo "${BLUE}Installing Libft ... ${DARKGRAY}"; 
	@$(MK) ./libs/libft;
	@git clone https://github.com/mathroy0310/42_libft.git ./libs/libft > /dev/null 2>&1;
	@make -C ./libs/libft > /dev/null 2>&1;
#@$(RM) ./libs/libft/Makefile ./libs/libft/bin ./libs/libft/src > /dev/null 2>&1;
	@echo "${BLUE}Libft successfully installed 🗄${DEFAULT}"


$(MLX) :
ifeq ($(shell uname), Linux)
	@echo "${BLUE}Installing MLX ... ${DARKGRAY}";
	@$(MK) ./libs/minilibx-linux;
	@git clone https://github.com/42Paris/minilibx-linux.git ./libs/minilibx-linux > /dev/null 2>&1;
	@make -C ./libs/minilibx-linux > /dev/null 2>&1;
	@echo "${BLUE}MLX successfully installed 🗄${DEFAULT}";

else ifeq ($(shell uname), Darwin)
	@echo "${BLUE}Installing MLX ... ${DARKGRAY}";
	@$(MK) ./libs/minilibx-mac-osx;
	@git clone https://github.com/dannywillems/minilibx-mac-osx.git ./libs/minilibx-mac-osx > /dev/null 2>&1;
	@make -C ./libs/minilibx-mac-osx > /dev/null 2>&1;
	@echo "${BLUE}MLX successfully installed 🗄${DEFAULT}";
else
	@echo "${RED}Error: MLX is not available on your system. 🚫${DEFAULT}"
endif

ifeq ($(shell uname -s), Linux)

	MLX = ./libs/minilibx-linux/libmlx.a  # or adjust for macOS
    MLXFLAGS = -L./libs/minilibx-linux -I./libs/minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
	CFLAGS += -I./libs/minilibx-linux
else ifeq ($(shell uname -s), Darwin) # macOS
    MLXFLAGS = -L./libs/minilibx-mac-osx -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -I./libs/minilibx-mac-osx
else
    $(error Unsupported operating system)
endif

$(NAME): $(BIN)
	@printf "\r${DARKGRAY}Compiling : $(NAME) ... ${DEFAULT}\033[K"
	@$(CC) $(CFLAGS) $(BIN) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "\r${GREEN}$(NAME) successfully created 🗄${DEFAULT}"

re: fclean all

clean		:
	@$(RM) bin
	@echo "${YELLOW}${NAME} binary files successfully removed 🗑${DEFAULT}"

lclean		:
	@$(RM) libs
	@echo "${YELLOW}Libraries successfully removed 🗑${DEFAULT}"

fclean		:	clean
	@${RM} ${NAME}
	@echo "${RED}${NAME} executable successfully removed 🗑${DEFAULT}"

#--- COLORS ---#

RED      = \033[1;31m
GREEN    = \033[1;32m
BLUE     = \033[1;34m
YELLOW   = \033[1;33m
DARKGRAY = \033[1;30m
DEFAULT  = \033[1;30m
