# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlager <jlager@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/18 11:48:28 by jlager            #+#    #+#              #
#    Updated: 2025/04/18 12:16:54 by jlager           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx
LIBFT_DIR = ./libft
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CFLAGS += -I. 
CFLAGS += -I$(MLX_DIR)
CFLAGS += -I$(LIBFT_DIR)

LDFLAGS = 
LDFLAGS += -L$(LIBFT_DIR) -lft
LDFLAGS += -L$(MLX_DIR) -lmlx

# Add OS-specific flags for MiniLibX
# macOS:
# LDFLAGS += -framework OpenGL -framework AppKit
# Linux:
LDFLAGS += -lXext -lX11 -lm -lz

SRCS =  main.c \
		map_reader_utils.c \
        map_reader.c \
		map_validation_utils.c \
        map_validation.c \
        game_init.c \
		game_render_utils.c \
        game_render.c \
        game_hooks.c \
        game_utils.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) executable created successfully."
%.o: %.c so_long.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@echo "Making Libft..."
	@$(MAKE) -C $(LIBFT_DIR)
$(MLX_LIB):
	@echo "Making MiniLibX..."
	@$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	@echo "Executable and Libft cleaned."

re: fclean all
.PHONY: all clean fclean re $(LIBFT_LIB) $(MLX_LIB)