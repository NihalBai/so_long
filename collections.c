/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:34 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 16:46:47 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_collections(char **map)
{
	int i = 0, j;
	int c= 0;

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
void initialize_game(t_data *game, char **map)
{
    game->collectibles_left = count_collections(map); 
}

void check_collectibles_and_exit(t_data *game)
{
    if (game->map_data[game->player.y][game->player.x] == 'C')
    {
        game->map_data[game->player.y][game->player.x] = '0'; 
        game->collectibles_left--;
        if (game->collectibles_left < 0)
            game->collectibles_left = 0;
    }
    if (game->map_data[game->player.y][game->player.x] == 'E' && game->collectibles_left == 0)
    {
        ft_putstr_fd("You win!\n", 1);
        mlx_destroy_window(game->mlx, game->win);
        exit(0); 
    }
}
