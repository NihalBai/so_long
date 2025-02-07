/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:56:32 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 17:17:52 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	initialize_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX\n", 2);
		return (1);
	}
	return (0);
}

static int	prepare_map(t_data *data, char **av)
{
	char	**map;

	map = read_map(av[1]);
	if (!map)
	{
		ft_putstr_fd("Error: Failed to read the map\n", 2);
		return (1);
	}
	data->map_data = map;
	count_map_width_height(map, &data->map);
	if (!validate_map(map) || !check_map_validity(map))
	{
		free_map(map);
		return (1);
	}
	return (0);
}

static int	initialize_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.w * 32, data->map.h * 32,
			"GAME");
	if (!data->win)
	{
		free_map(data->map_data);
		ft_putstr_fd("Error: Failed to create window\n", 2);
		return (1);
	}
	return (0);
}

static void	setup_game(t_data *data)
{
	initialize_images(data);
	load_player_textures(data);
	load_enemy_textures(data);
	initialize_player(data, data->map_data);
	initialize_enemy(data, data->map_data);
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 17, 1L << 5, close_handler, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./so_long <map_file>\n", 2);
		return (1);
	}
	if (initialize_data(&data) || prepare_map(&data, av)
		|| initialize_window(&data))
		return (1);
	setup_game(&data);
	draw_map(&data, data.map_data);
	mlx_loop(data.mlx);
	cleanup_textures(&data);
	free_map(data.map_data);
	return (0);
}
