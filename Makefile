# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 19:10:11 by nbaidaou          #+#    #+#              #
#    Updated: 2025/02/06 16:16:22 by nbaidaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Iget_next_line -Iminilibx-linux-master
LDFLAGS = -Llibft -Lget_next_line -Lminilibx-linux-master

# Directories
MLX_DIR = minilibx-linux-master
LIBFT_DIR = libft
GNL_DIR = get_next_line

# Source files and object files
SRC = window.c map_validation.c moves.c enemy.c helpers.c
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
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -l:get_next_line.a -L$(MLX_DIR) $(MLX_LIB) -o $(NAME)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files in the current directory, libft, and get_next_line
clean:
	rm -f $(OBJ)  # Delete object files in the current directory
	$(MAKE) -C $(LIBFT_DIR) clean  # Clean object files in libft
	$(MAKE) -C $(GNL_DIR) clean  # Clean object files in get_next_line

# Clean everything (including libraries and binaries)
fclean: clean
	rm -f $(NAME)  # Delete the final binary
	$(MAKE) -C $(LIBFT_DIR) fclean  # Clean libft (including its library)
	$(MAKE) -C $(GNL_DIR) fclean  # Clean get_next_line (including its library)

# Rebuild everything
re: fclean all

# Makefile rule for libft and get_next_line
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL_LIB):
	$(MAKE) -C $(GNL_DIR)

.PHONY: all clean fclean re