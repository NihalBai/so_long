/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:59 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/08 00:21:41 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_width_height(char **map, t_map *map_info)
{
	int	i;

	map_info->w = 0;
	map_info->h = 0;
	i = 0;
	while (map[i] != NULL)
	{
		map_info->h++;
		i++;
	}
	if (map[0] != NULL)
	{
		i = 0;
		while (map[0][i] != '\0')
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
	if (!data->wall_textures || !data->floor_textures || !data->collect_textures
		|| !data->exit_textures)
	{
		ft_putstr_fd("Error: Failed to load one or more XPM images.\n", 2);
		exit(EXIT_FAILURE);
	}
	load_player_textures(data);
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

