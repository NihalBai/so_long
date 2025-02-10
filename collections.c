/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:34 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/08 23:09:11 by nbaidaou         ###   ########.fr       */
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
			ft_putstr_fd("You win!\n", 1);
			close_handler(game);
		}
	}
}
