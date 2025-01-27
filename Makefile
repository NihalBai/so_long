# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 19:10:11 by nbaidaou          #+#    #+#              #
#    Updated: 2025/01/27 16:37:29 by nbaidaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Iget_next_line -Imlx  # Add include paths
LDFLAGS = -Llibft -Lget_next_line  # Link the libft and get_next_line directories

# Directories
MLX_DIR = mlx
LIBFT_DIR = libft
GNL_DIR = get_next_line

# Source files and object files
SRC = window.c
OBJ = $(SRC:.c=.o)

# Library files
LIBFT_LIB = $(LIBFT_DIR)/libft.a
GNL_LIB = $(GNL_DIR)/get_next_line.a
MLX_LIB = -lmlx_Linux -lX11 -lXext -lm

# Output binary
NAME = window

# Default target
all: $(NAME)

# Link object files into the final executable
$(NAME): $(OBJ) $(LIBFT_LIB) $(GNL_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT_LIB) $(GNL_LIB) $(MLX_LIB) -o $(NAME)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Clean everything (including libraries)
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_LIB) $(GNL_LIB)

# Rebuild everything
re: fclean all

# Makefile rule for libft and get_next_line
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL_LIB):
	$(MAKE) -C $(GNL_DIR)

.PHONY: all clean fclean re

