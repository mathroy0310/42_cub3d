# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 16:01:23 by maroy             #+#    #+#              #
#    Updated: 2024/01/24 14:37:52 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I./inc -std=c99 -O3

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS += -I$(LIBFT_DIR)/inc -L$(LIBFT_DIR) -lft

LIBFT	= ./libs/libft/libft.a
# ifeq ($(shell uname), Linux)
# 	MLX		= ./libs/minilibx-linux/libmlx.a
# else ifeq ($(shell uname), Darwin)
# 	MLX		= ./libs/minilibx-mac-osx/libmlx.a
# else
# 	@echo "${RED}Error: MLX is not available on your system. 🚫${DEFAULT}"
# endif
MLX = ./libs/MLX42/build/libmlx42.a

SRC_MAIN_DIR		= src
SRC_PARSING_DIR 	= 	$(SRC_MAIN_DIR)/parsing
SRC_GAME_DIR		=	$(SRC_MAIN_DIR)/game
SRC_MINIMAP_DIR		=	$(SRC_MAIN_DIR)/minimap
SRCS_RAYCASTING_DIR =	$(SRC_MAIN_DIR)/raycasting
SRC_GRAPHICS_DIR	=	$(SRC_MAIN_DIR)/graphics

SRCS_MAIN	=	main.c \
				debug.c

SRCS_PARSING =  valid.c \
				parsing.c \
				parsing_utils.c \

SRCS_GAME 	=	init.c \
				player_movement.c \
				hook_events.c \
				

SRCS_MINIMAP = 	minimap.c \
				minimap_utils.c \

SRCS_RAYCASTING = raycasting.c \
				

SRCS_GRAPHICS =	draw.c \
  				texturing.c \

SRC += $(addprefix $(SRC_MAIN_DIR)/, $(SRCS_MAIN))
SRC += $(addprefix $(SRC_PARSING_DIR)/, $(SRCS_PARSING))
SRC += $(addprefix $(SRC_GAME_DIR)/, $(SRCS_GAME))
SRC += $(addprefix $(SRC_MINIMAP_DIR)/, $(SRCS_MINIMAP))
SRC += $(addprefix $(SRCS_RAYCASTING_DIR)/, $(SRCS_RAYCASTING)) 
SRC += $(addprefix $(SRC_GRAPHICS_DIR)/, $(SRCS_GRAPHICS))


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

	@echo "${BLUE}Installing MLX42 ... ${DARKGRAY}";
	@git clone https://github.com/codam-coding-college/MLX42.git ./libs/MLX42 > /dev/null 2>&1;
	@cmake -B ./libs/MLX42/build -S ./libs/MLX42
	@cmake --build ./libs/MLX42/build -j4
	@echo "${BLUE}MLX successfully installed 🗄${DEFAULT}";

ifeq ($(shell uname -s), Linux)
    MLXFLAGS = -L./libs/MLX42/build -I./libs/MLX42/include/MLX42 -ldl -lmlx42 -lglfw -pthread -lm
	CFLAGS += 
else ifeq ($(shell uname -s), Darwin) # macOS
    MLXFLAGS = -L./libs/MLX42/build -I./libs/MLX42/include/MLX42 -framework Cocoa -framework OpenGL -framework IOKit
	CFLAGS += -lmlx42 -lglfw
	CFLAGS += -L"/Users/${USER}/homebrew/Cellar/glfw/3.3.9/lib"
	CFLAGS += -L"/Users/${USER}/.brew/opt/glfw/lib"
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
