/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:24:33 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 17:17:11 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG
# define SO_LONG

# include "./minilibx-linux-master/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef struct s_player
{
	int x;                // Player X position
	int y;                // Player Y position
	void *textures[4][2]; // Player movement textures [direction][frame]
	int current_frame;    // Toggle between 0 and 1 for animation
	int direction;        // 0 = down, 1 = left, 2 = right, 3 = up
}				t_player;

typedef struct s_enemy
{
	int			x;
	int			y;
	void		*textures_enemy[7];
	int			current_frame_enemy;
}				t_enemy;

typedef struct s_map
{
	int w; // Map width (columns)
	int h; // Map height (rows)
}				t_map;

typedef struct s_data
{
	void *mlx;           // MiniLibX instance
	void *win;           // Window instance
	void *textures;      // Image instance
	char *addr;          // Image data address
	int bpp;             // Bits per pixel
	int textures_width;  // Texture width
	int textures_height; // Texture height
	int line_length;     // Line length of the image
	int endian;          // Endianness of the image

	char		**map_data;

	// Image assets
	void *wall_textures;    // Wall texture
	void *floor_textures;   // Floor texture
	void *player_textures;  // Player texture
	void *collect_textures; // Collectible texture
	void *exit_textures;    // Exit texture

	int			collectibles_left;
	t_player	player;
	t_map		map;
	t_enemy		enemy;
}				t_data;

// initialization
void			count_map_width_height(char **map, t_map *map_info);
void			initialize_images(t_data *data);
void			initialize_player(t_data *data, char **map);
void			*choose_textures(t_data *data, char tile);

// entities
void			cleanup_textures(t_data *data);
void			draw_entities(t_data *data);
void			destroy_single_textures(t_data *data);
void			destroy_enemy_textures(void *mlx, void *textures[7]);
void			destroy_texture_group(void *mlx, void *textures[4][2]);

// map_validation
int				validate_map(char **map);
void			flood_fill(char **map, int x, int y, int *visited);
int				find_player(char **map, int *start_x, int *start_y);
int				check_map_fully_connected(char **map, int *visited);
int				check_map_validity(char **map);

// moves
void			render_player(t_data *game);
int				handle_keypress(int keycode, t_data *game);
void			load_player_textures(t_data *game);
void			move_player(t_data *data, char **map, int new_x, int new_y,
					int direction);

// f_map
void			draw_map(t_data *data, char **map);
char			**read_map(const char *file);

// enemy
void			game_loop(t_data *game);
void			initialize_enemy(t_data *data, char **map);
void			move_enemy(t_data *data);
void			load_enemy_textures(t_data *game);
void			animate_enemy(t_data *game);

// helpers
int				ft_rand(void);
void			ft_srand(unsigned int new_seed);
void			free_map(char **map);
int				close_handler(t_data *vars);

// collections
void			check_collectibles_and_exit(t_data *game);

#endif
