/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:34 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/11 15:07:23 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	count_collections(char **map)
{
	int		i;
	int		j;
	size_t	c;

	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}
void	print_map(t_data *game)
{
	int y = 0;
	int x;

	while (y < game->map.h)
	{
		x = 0;
		while (x < game->map.w)
		{
			ft_putchar_fd(game->map_data[y][x], 1); // Print each tile
			x++;
		}
		ft_putchar_fd('\n', 1); // Newline after each row
		y++;
	}
}

void	check_collectibles_and_exit(t_data *game)
{
	if (game->map_data[game->player.y][game->player.x] == 'C')
	{
		game->map_data[game->player.y][game->player.x] = '0';
		if (game->collectibles_left > 0)
			game->collectibles_left--;
	}
	if (game->map_data[game->player.y][game->player.x] == 'E')
	{
		if (game->collectibles_left == 0)
		{
			game->game_won = 1;
			game->map_data[game->player.y][game->player.x] = 'W';
			mlx_clear_window(game->mlx, game->win);
			draw_map(game, game->map_data); 
			mlx_do_sync(game->mlx);  
			ft_putstr_fd("You win!\n", 1);
			usleep(2000000);  
			
			close_handler(game);
		}
	}
}
// void	check_collectibles_and_exit(t_data *game)
// {
// 	if (game->map_data[game->player.y][game->player.x] == 'C')
// 	{
// 		game->map_data[game->player.y][game->player.x] = '0';
// 		if (game->collectibles_left > 0)
// 			game->collectibles_left--;
// 	}
// 	if (game->map_data[game->player.y][game->player.x] == 'E')
// 	{
// 		if (game->collectibles_left == 0)
// 		{
// 			ft_putstr_fd("You win!\n", 1);
// 			close_handler(game);
// 		}
// 	}
// }
