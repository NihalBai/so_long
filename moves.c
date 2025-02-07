/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:20:35 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 15:21:11 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_player(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				data->player.x = x;
				data->player.y = y;
				data->player.direction = 0;
				data->player.current_frame = 0;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	render_player(t_data *game)
{
	void	*current_texture;

	current_texture = game->player.textures[game->player.direction][game->player.current_frame];
	mlx_put_image_to_window(game->mlx, game->win, current_texture,
		game->player.x * 32, game->player.y * 32);
}

void	move_player(t_data *data, char **map, int new_x, int new_y,
		int direction)
{
	if (map[new_y][new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
		data->player.direction = direction;
		data->player.current_frame = !data->player.current_frame;
	}
}

// void	process_movement(int keycode, t_data *game, int *player_moved)
// {
// 	int	prev_x;
// 	int	prev_y;

// 	prev_x = game->player.x;
// 	prev_y = game->player.y;
// 	if (keycode == 119 || keycode == 65362)
// 		move_player(game, game->map_data, game->player.x, game->player.y - 1,
// 			3);
// 	else if (keycode == 115 || keycode == 65364)
// 		move_player(game, game->map_data, game->player.x, game->player.y + 1,
// 			0);
// 	else if (keycode == 97 || keycode == 65361)
// 		move_player(game, game->map_data, game->player.x - 1, game->player.y,
// 			1);
// 	else if (keycode == 100 || keycode == 65363)
// 		move_player(game, game->map_data, game->player.x + 1, game->player.y,
// 			2);
// 	else
// 		return ;
// 	if (game->player.x != prev_x || game->player.y != prev_y)
// 		(*player_moved)++;
// }

void process_movement(int keycode, t_data *game, int *player_moved)
{
    int prev_x = game->player.x;
    int prev_y = game->player.y;

    if (keycode == 119 || keycode == 65362)
        move_player(game, game->map_data, game->player.x, game->player.y - 1, 3);
    else if (keycode == 115 || keycode == 65364)
        move_player(game, game->map_data, game->player.x, game->player.y + 1, 0);
    else if (keycode == 97 || keycode == 65361)
        move_player(game, game->map_data, game->player.x - 1, game->player.y, 1);
    else if (keycode == 100 || keycode == 65363)
        move_player(game, game->map_data, game->player.x + 1, game->player.y, 2);

    if (game->player.x != prev_x || game->player.y != prev_y)
        (*player_moved)++;
}

void check_game_status(t_data *game, int player_moved)
{
    if (player_moved > 0 && player_moved % 4 == 0)
        move_enemy(game);
    if (game->player.x == game->enemy.x && game->player.y == game->enemy.y)
    {
        ft_putstr_fd("Game Over! Enemy caught you!\n", 1);
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
}

// int	handle_keypress(int keycode, t_data *game)
// {
// 	static int	player_moved = 0;

// 	if (keycode == 65307)
// 	{
// 		mlx_destroy_window(game->mlx, game->win);
// 		exit(0);
// 	}
// 	else
// 		process_movement(keycode, game, &player_moved);
// 	check_game_status(game, player_moved);
// 	mlx_clear_window(game->mlx, game->win);
// 	draw_map(game, game->map_data);
// 	return (0);
// }
int	handle_keypress(int keycode, t_data *game)
{
	static int	player_moved = 0;

	if (keycode == 65307)  // Escape key
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else
		process_movement(keycode, game, &player_moved);
	
	ft_putstr_fd("Total moves: ", 1);
	ft_putnbr_fd(player_moved, 1);
	ft_putchar_fd('\n', 1);

	check_game_status(game, player_moved);
	mlx_clear_window(game->mlx, game->win);
	draw_map(game, game->map_data);
	return (0);
}
void	load_player_textures(t_data *game)
{
	game->player.textures[0][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/bunny.xpm", &game->textures_width,
			&game->textures_height);
	game->player.textures[0][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/bunny1.xpm", &game->textures_width,
			&game->textures_height);
	game->player.textures[1][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/right.xpm", &game->textures_width,
			&game->textures_height);
	game->player.textures[1][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/right1.xpm", &game->textures_width,
			&game->textures_height);
	game->player.textures[2][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/left.xpm", &game->textures_width, &game->textures_height);
	game->player.textures[2][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/left1.xpm", &game->textures_width,
			&game->textures_height);
	game->player.textures[3][0] = mlx_xpm_file_to_image(game->mlx,
			"textures/back.xpm", &game->textures_width, &game->textures_height);
	game->player.textures[3][1] = mlx_xpm_file_to_image(game->mlx,
			"textures/back1.xpm", &game->textures_width,
			&game->textures_height);
}
