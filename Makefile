# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 19:10:11 by nbaidaou          #+#    #+#              #
#    Updated: 2025/02/12 23:13:00 by nbaidaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Iget_next_line -Iminilibx-linux-master
LDFLAGS = -Llibft -Lget_next_line -Lminilibx-linux-master

MLX_DIR = /home/nbaidaou/Documents/minilibx-linux-master
LIBFT_DIR = libft
GNL_DIR = get_next_line

SRC = window.c map_validation.c moves.c enemy_bonus.c helpers.c collections.c entities.c initialization.c f_map.c enemy2_bonus.c helpers1.c
OBJ = $(SRC:.c=.o)


LIBFT_LIB = $(LIBFT_DIR)/libft.a
GNL_LIB = $(GNL_DIR)/get_next_line.a
MLX_LIB = -lmlx_Linux -lX11 -lXext -lm

NAME = window

all: $(NAME)
	@echo "✅ Build successful!"

$(NAME): $(OBJ) $(LIBFT_LIB) $(GNL_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -l:get_next_line.a -L$(MLX_DIR) $(MLX_LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)  
	@$(MAKE) -C $(LIBFT_DIR) clean  
	@$(MAKE) -C $(GNL_DIR) clean  
	@echo "🧹 Cleaned object files!"

fclean: clean
	@rm -f $(NAME) 
	@$(MAKE) -C $(LIBFT_DIR) fclean 
	@$(MAKE) -C $(GNL_DIR) fclean  
	@echo "🗑️ Fully cleaned project!"


re: fclean all


$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL_LIB):
	@$(MAKE) -C $(GNL_DIR)
	
.PHONY: all clean fclean re