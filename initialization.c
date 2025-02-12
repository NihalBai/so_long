/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:59 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/12 22:59:40 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_width_height(char **map, t_map *map_info)
{
	int	first_valid_line;
	int	last_valid_line;
	int	i;

	find_map_bounds(map, &first_valid_line, &last_valid_line);
	map_info->w = 0;
	map_info->h = 0;
	if (first_valid_line != -1)
		map_info->h = last_valid_line - first_valid_line + 1;
	if (first_valid_line != -1)
	{
		i = 0;
		while (map[first_valid_line][i] != '\0')
		{
			map_info->w++;
			i++;
		}
	}
}

void	initialize_images(t_data *data)
{
	data->wall_textures = mlx_xpm_file_to_image(data->mlx, "textures/Cold.xpm",
			&data->textures_width, &data->textures_height);
	data->floor_textures = mlx_xpm_file_to_image(data->mlx, "textures/gass.xpm",
			&data->textures_width, &data->textures_height);
	data->collect_textures = mlx_xpm_file_to_image(data->mlx,
			"textures/rose.xpm", &data->textures_width, &data->textures_height);
	data->exit_textures = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm",
			&data->textures_width, &data->textures_height);
	data->win_texture = mlx_xpm_file_to_image(data->mlx, "textures/win.xpm",
			&data->textures_width, &data->textures_height);
	data->lose_texture = mlx_xpm_file_to_image(data->mlx, "textures/lose.xpm",
			&data->textures_width, &data->textures_height);
	if (!data->wall_textures || !data->floor_textures || !data->collect_textures
		|| !data->exit_textures || !data->win_texture)
	{
		ft_putstr_fd("Error: Failed to load one or more XPM images.\n", 2);
		close_handler(data);
	}
}

void	initialize_player(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	data->collectibles_left = count_collections(map);
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

void	*choose_textures(t_data *data, char tile)
{
	if (tile == 'L' && data->lose_texture)
		return (data->lose_texture);
	if (tile == 'W')
		return (data->win_texture);
	if (tile == '1')
		return (data->wall_textures);
	if (tile == '0')
		return (data->floor_textures);
	if (tile == 'P')
		return (data->floor_textures);
	if (tile == 'C')
		return (data->collect_textures);
	if (tile == 'E')
		return (data->exit_textures);
	if (tile == 'M')
		return (data->floor_textures);
	return (NULL);
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
