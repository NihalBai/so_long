/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:24:33 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/15 21:18:53 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/home/nbaidaou/Documents/minilibx-linux-master/mlx.h"
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
	int			x;
	int			y;
	void		*textures[4][2];
	int			current_frame;
	int			direction;
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
	int			w;
	int			h;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*textures;
	char		*addr;
	int			bpp;
	int			textures_width;
	int			textures_height;
	int			line_length;
	int			endian;
	char		**map_data;
	void		*wall_textures;
	void		*floor_textures;
	void		*collect_textures;
	void		*exit_textures;
	void		*win_texture;
	void		*lose_texture;
	size_t		collectibles_left;
	t_player	player;
	t_map		map;
	t_enemy		enemy;
	int			game_won;
	int			game_lost;
}				t_data;

typedef struct s_map_counts
{
	int			p;
	int			e;
	int			c;
}				t_map_counts;

/*
** INITIALIZATION
*/
void			count_map_width_height(char **map, t_map *map_info);
void			initialize_images(t_data *data);
void			initialize_player(t_data *data, char **map);
void			*choose_textures(t_data *data, char tile);
void			load_player_textures(t_data *game);

/*
** ENTITIES
*/
void			cleanup_textures(t_data *data);
void			draw_entities(t_data *data);
void			destroy_single_textures(t_data *data);
void			destroy_enemy_textures(void *mlx, void *textures[7]);
void			destroy_texture_group(void *mlx, void *textures[4][2]);

/*
** MAP VALIDATION
*/
int				validate_map(char **map);
void			flood_fill(char **map, int x, int y, int *visited);
int				find_player(char **map, int *start_x, int *start_y);
int				check_map_fully_connected(char **map, int *visited);
int				check_map_validity(char **map);

/*
** MOVES
*/
void			render_player(t_data *game);
int				handle_keypress(int keycode, t_data *game);
void			move_player(t_data *data, int new_x, int new_y, int direction);

/*
** FILE MAP
*/
void			draw_map(t_data *data, char **map);
char			**read_map(const char *file, t_data *data);

/*
** ENEMY
*/
int				game_loop(void *param);
void			initialize_enemy(t_data *data, char **map);
void			move_enemy(t_data *data);
void			load_enemy_textures(t_data *game);
void			animate_enemy(t_data *game);

/*
** HELPERS
*/
int				ft_rand(void);
void			ft_srand(unsigned int new_seed);
void			free_map(char **map);
int				close_handler(t_data *vars);
void			win_lose(t_data *data, int win);
int				find_last_valid_line(char **map);
void			find_map_bounds(char **map, int *first, int *last);
int				count_map_elements(char **map, int last_valid_line,
					t_map_counts *counts);
void			counter(t_data *data, int c);
/*
** COLLECTIONS
*/
void			check_collectibles_and_exit(t_data *game);
size_t			count_collections(char **map);

#endif
