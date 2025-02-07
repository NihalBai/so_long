/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:06:47 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 16:59:16 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_enemy(t_data *data, char **map)
{
	int			attempts;
	const int	MAX_ATTEMPTS = 100;

	int x, y;
	attempts = 0;
	data->enemy.current_frame_enemy = 0;
	while (attempts < MAX_ATTEMPTS)
	{
		y = ft_rand() % data->map.h;
		x = ft_rand() % data->map.w;
		if (map[y][x] == '0' && !(x == data->player.x && y == data->player.y))
		{
			data->enemy.x = x;
			data->enemy.y = y;
			map[y][x] = 'M';
			return ;
		}
		attempts++;
	}
	ft_putstr_fd("Warning: Could not place enemy after maximum attempts\n", 2);
}

void	count_empty_spaces(t_data *data, int *count)
{
	int	i;
	int	j;

	i = 0;
	*count = 0;
	while (i < data->map.h)
	{
		j = 0;
		while (j < data->map.w)
		{
			if (data->map_data[i][j] == '0')
				(*count)++;
			j++;
		}
		i++;
	}
}

void	fill_empty_spaces(t_data *data, int *x, int *y, int *count)
{
	int	i;
	int	j;

	i = 0;
	*count = 0;
	while (i < data->map.h)
	{
		j = 0;
		while (j < data->map.w)
		{
			if (data->map_data[i][j] == '0')
				x[*count] = j, y[(*count)++] = i;
			j++;
		}
		i++;
	}
}

void	get_empty_spaces(t_data *data, int **x, int **y, int *count)
{
	count_empty_spaces(data, count);
	*x = malloc(*count * sizeof(int));
	*y = malloc(*count * sizeof(int));
	if (!(*x) || !(*y))
		return ;
	fill_empty_spaces(data, *x, *y, count);
}



void move_enemy(t_data *data)
{
    static int last_x = -1, last_y = -1;
    int r, *x, *y, count = 0;

    get_empty_spaces(data, &x, &y, &count);
    if (count > 0)
    {
        r = ft_rand() % count;
        int new_x = x[r];
        int new_y = y[r];

        if (new_x != last_x || new_y != last_y)
        {
            // Enemy moved, update its position and reset animation
            data->map_data[data->enemy.y][data->enemy.x] = '0'; // Reset old position
            data->enemy.x = new_x;
            data->enemy.y = new_y;
            data->map_data[new_y][new_x] = 'M'; // Place enemy in new position
            data->enemy.current_frame_enemy = 0; // Reset animation when moving
        }
        else
        {
            // Enemy stayed in the same position, animate
            animate_enemy(data);
        }
        last_x = data->enemy.x;
        last_y = data->enemy.y;
    }
    free(x);
    free(y);
}
// void move_enemy(t_data *data)
// {
//     int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
//     int dir = rand() % 4;
//     int new_x = data->enemy.x + directions[dir][0];
//     int new_y = data->enemy.y + directions[dir][1];

//     if (new_x >= 0 && new_x < data->map.w && 
//         new_y >= 0 && new_y < data->map.h && 
//         data->map_data[new_y][new_x] == '0')
//     {
//         data->map_data[data->enemy.y][data->enemy.x] = '0';
//         data->enemy.x = new_x;
//         data->enemy.y = new_y;
//         data->map_data[new_y][new_x] = 'M';
//     }
// }
// void	load_player_textures_enemy(t_data *game)
// {
// 	game->enemy.textures_enemy[0][0] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/1.xpm", &game->textures_width, &game->textures_height);
// 	game->enemy.textures_enemy[0][1] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/2.xpm", &game->textures_width, &game->textures_height);
// 	game->enemy.textures_enemy[1][0] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/3.xpm", &game->textures_width, &game->textures_height);
// 	game->enemy.textures_enemy[1][1] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/4.xpm", &game->textures_width, &game->textures_height);
// 	game->enemy.textures_enemy[2][0] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/5.xpm", &game->textures_width, &game->textures_height);
// 	game->enemy.textures_enemy[2][1] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/6.xpm", &game->textures_width, &game->textures_height);
// 	game->enemy.textures_enemy[3][0] = mlx_xpm_file_to_image(game->mlx,
// 			"textures/7.xpm", &game->textures_width, &game->textures_height);
// }

void load_enemy_textures(t_data *game)
{
    char *textures[7] = {
        "textures/1.xpm", "textures/2.xpm", "textures/3.xpm",
        "textures/4.xpm", "textures/5.xpm", "textures/6.xpm", "textures/7.xpm"
    };
    int i = 0;

    while (i < 7)
    {
        game->enemy.textures_enemy[i] = mlx_xpm_file_to_image(
            game->mlx, textures[i], &game->textures_width, &game->textures_height);
        if (!game->enemy.textures_enemy[i])
            ft_putstr_fd("Error loading enemy texture!\n", 2);
        i++;
    }
}




void animate_enemy(t_data *game)
{
    // Debugging the current frame before and after update
    printf("Before animation: frame %d\n", game->enemy.current_frame_enemy);
    game->enemy.current_frame_enemy = (game->enemy.current_frame_enemy + 1) % 7;
    printf("After animation: frame %d\n", game->enemy.current_frame_enemy);
}



void game_loop(t_data *game)
{
    static int frame_counter = 0;

    // Print the frame_counter to see if animate_enemy is called regularly
    printf("Frame counter: %d\n", frame_counter);

    if (frame_counter++ % 10 == 0) // Change every 10 frames (adjust as needed)
        animate_enemy(game);

    move_enemy(game);  // Move the enemy based on random selection
    draw_map(game, game->map_data); // Redraw the map including the enemy
}






