# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 19:10:11 by nbaidaou          #+#    #+#              #
#    Updated: 2025/02/13 22:47:00 by nbaidaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Iget_next_line -Iminilibx-linux-master

MLX_DIR = /home/nbaidaou/Documents/minilibx-linux-master
LIBFT_DIR = libft
GNL_DIR = get_next_line

SRC_B = bonus/window_bonus.c bonus/map_validation_bonus.c bonus/moves_bonus.c bonus/enemy_bonus.c bonus/helpers_bonus.c bonus/collections_bonus.c bonus/entities_bonus.c bonus/initialization_bonus.c bonus/f_map_bonus.c bonus/enemy2_bonus.c bonus/helpers1_bonus.c
SRC_M = mandatory/window.c mandatory/map_validation.c mandatory/moves.c  mandatory/helpers.c mandatory/collections.c mandatory/entities.c mandatory/initialization.c mandatory/f_map.c  mandatory/helpers1.c
OBJ_M = $(SRC_M:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

LIBFT_LIB = $(LIBFT_DIR)/libft.a
GNL_LIB = $(GNL_DIR)/get_next_line.a
MLX_LIB = -lmlx_Linux -lX11 -lXext -lm

NAME = so_long
NAME_BONUS = so_long_bonus

all: $(NAME)
	@echo "✅ Build successful!"

$(NAME): $(OBJ_M) $(LIBFT_LIB) $(GNL_LIB)
	@$(CC) $(CFLAGS) $(OBJ_M) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -l:get_next_line.a -L$(MLX_DIR) $(MLX_LIB) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_B) $(LIBFT_LIB) $(GNL_LIB)
	@$(CC) $(CFLAGS) $(OBJ_B) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -l:get_next_line.a -L$(MLX_DIR) $(MLX_LIB) -o $(NAME_BONUS)
	@echo "🎉 Bonus Build successful!"
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_M) $(OBJ_B)  
	@$(MAKE) -C $(LIBFT_DIR) clean  
	@$(MAKE) -C $(GNL_DIR) clean  
	@echo "🧹 Cleaned object files!"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean 
	@$(MAKE) -C $(GNL_DIR) fclean  
	@echo "🗑️ Fully cleaned project!"


re: fclean all


$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL_LIB):
	@$(MAKE) -C $(GNL_DIR)
	
.PHONY: all clean fclean re
