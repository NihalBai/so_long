/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:20:35 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/10 01:05:32 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	process_movement(int keycode, t_data *game, int *player_moved)
{
	int	prev_x;
	int	prev_y;

	prev_x = game->player.x;
	prev_y = game->player.y;
	if (keycode == 119 || keycode == 65362)
		move_player(game, game->map_data, game->player.x, game->player.y - 1,
			3);
	else if (keycode == 115 || keycode == 65364)
		move_player(game, game->map_data, game->player.x, game->player.y + 1,
			0);
	else if (keycode == 97 || keycode == 65361)
		move_player(game, game->map_data, game->player.x - 1, game->player.y,
			1);
	else if (keycode == 100 || keycode == 65363)
		move_player(game, game->map_data, game->player.x + 1, game->player.y,
			2);
	if (game->player.x != prev_x || game->player.y != prev_y)
		(*player_moved)++;
	check_collectibles_and_exit(game);
}

void	check_game_status(t_data *game, int player_moved)
{
	if (player_moved > 0 && player_moved % 10 == 0)
		move_enemy(game);
	if (game->player.x == game->enemy.x && game->player.y == game->enemy.y)
	{
		ft_putstr_fd("Game Over! Enemy caught you!\n", 1);
		close_handler(game);
	}
}

int	handle_keypress(int keycode, t_data *game)
{
	static int	player_moved = 0;

	if (keycode == 65307)
	{
		close_handler(game);
		return (0);
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
