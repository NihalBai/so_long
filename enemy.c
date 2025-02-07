/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:06:47 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 15:18:48 by nbaidaou         ###   ########.fr       */
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
		y = rand() % data->map.h;
		x = rand() % data->map.w;
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

// void move_enemy(t_data *data)
// {
//     int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
//     int dir = rand() % 4;
//     int new_x = data->enemy.x + directions[dir][0];
//     int new_y = data->enemy.y + directions[dir][1];

//     if (new_x >= 0 && new_x < data->map.w && new_y >= 0
//&&new_y < data->map.h
//         && data->map_data[new_y][new_x] == '0')
//     {
//         data->map_data[data->enemy.y][data->enemy.x] = '0';
//         data->enemy.x = new_x;
//         data->enemy.y = new_y;
//         data->map_data[new_y][new_x] = 'M';
//     }
// }


// void	get_empty_spaces(t_data *data, int **x, int **y, int *count)
// {
// 	int i = 0, j;

// 	*count = 0;
// 	while (i < data->map.h)
// 	{
// 		j = 0;
// 		while (j < data->map.w)
// 		{
// 			if (data->map_data[i][j] == '0' || data->map_data[i][j] == 'M') 
// 				(*count)++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	*x = malloc(*count * sizeof(int));
// 	*y = malloc(*count * sizeof(int));

// 	*count = 0;
// 	i = 0;
// 	while (i < data->map.h)
// 	{
// 		j = 0;
// 		while (j < data->map.w)
// 		{
// 			if (data->map_data[i][j] == '0' || data->map_data[i][j] == 'M')
// 			{
// 				(*x)[*count] = j;
// 				(*y)[*count] = i;
// 				(*count)++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
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


void	move_enemy(t_data *data)
{
	int r, *x, *y, count = 0;

	get_empty_spaces(data, &x, &y, &count);
	if (count > 0)
	{
		r = rand() % count;
		data->map_data[data->enemy.y][data->enemy.x] = '0'; // Reset old position
		data->enemy.x = x[r];
		data->enemy.y = y[r];
		data->map_data[y[r]][x[r]] = 'M'; // Place enemy in new position
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
void	load_player_textures_enemy(t_data *game)
{
	game->enemy.textures_enemy[0][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/1.xpm", &game->textures_width, &game->textures_height);
	game->enemy.textures_enemy[0][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/2.xpm", &game->textures_width, &game->textures_height);
	game->enemy.textures_enemy[1][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/3.xpm", &game->textures_width, &game->textures_height);
	game->enemy.textures_enemy[1][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/4.xpm", &game->textures_width, &game->textures_height);
	game->enemy.textures_enemy[2][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/5.xpm", &game->textures_width, &game->textures_height);
	game->enemy.textures_enemy[2][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/6.xpm", &game->textures_width, &game->textures_height);
	game->enemy.textures_enemy[3][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/7.xpm", &game->textures_width, &game->textures_height);
}
