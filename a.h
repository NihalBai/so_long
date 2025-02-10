/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:24:33 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/09 14:31:32 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A
# define A

# include "./minilibx-linux-master/mlx.h"
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

	size_t		collectibles_left;
	t_player	player;
	t_map		map;
	t_enemy		enemy;
}				t_data;


#endif
