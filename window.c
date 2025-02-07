/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:56:32 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 14:22:51 by nbaidaou         ###   ########.fr       */
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

// Function to handle key presses

int	close_handler(t_data *vars)
{
	ft_putstr_fd("Window closed via close button.\n", 1);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
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
void	destroy_texture_group(void *mlx, void *textures[4][2])
{
	int i, j;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 2)
		{
			if (textures[i][j])
				mlx_destroy_image(mlx, textures[i][j]);
			j++;
		}
		i++;
	}
}

void	destroy_single_textures(t_data *data)
{
	if (data->wall_textures)
		mlx_destroy_image(data->mlx, data->wall_textures);
	if (data->floor_textures)
		mlx_destroy_image(data->mlx, data->floor_textures);
	if (data->collect_textures)
		mlx_destroy_image(data->mlx, data->collect_textures);
	if (data->exit_textures)
		mlx_destroy_image(data->mlx, data->exit_textures);
}

void	cleanup_textures(t_data *data)
{
	destroy_texture_group(data->mlx, data->player.textures);
	destroy_texture_group(data->mlx, data->enemy.textures_enemy);
	destroy_single_textures(data);
}

void	draw_entities(t_data *data)
{
	void	*player_tex;
	void	*enemy_tex;

	player_tex = data->player.textures[data->player.direction][data->player.current_frame];
	enemy_tex = data->enemy.textures_enemy[0][0];
	if (player_tex)
		mlx_put_image_to_window(data->mlx, data->win, player_tex, data->player.x
			* 32, data->player.y * 32);
	if (enemy_tex)
		mlx_put_image_to_window(data->mlx, data->win, enemy_tex, data->enemy.x
			* 32, data->enemy.y * 32);
}
void	draw_map(t_data *data, char **map)
{
	void	*current_textures;

	int(x), (y);
	y = 0;
	while (y < data->map.h)
	{
		x = 0;
		while (x < data->map.w)
		{
			current_textures = choose_textures(data, map[y][x]);
			if (current_textures)
				mlx_put_image_to_window(data->mlx, data->win, current_textures,
					x * 32, y * 32);
			x++;
		}
		y++;
	}
	draw_entities(data);
}
char	**read_map(const char *file)
{
	int		fd;
	char	*line;
	char	**map;
	size_t	row_count;
	size_t	i;
	char	*trimmed_line;

	row_count = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Could not open map file\n", 2), NULL);
	while ((line = get_next_line(fd)) != NULL)
	{
		row_count++;
		free(line);
	}
	close(fd);
	map = (char **)malloc((row_count + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Could not reopen map file\n", 2),
			free(map), NULL);
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed_line = ft_strtrim(line, "\n");
		map[i++] = ft_strdup(trimmed_line);
		free(trimmed_line);
		free(line);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// int	main(int ac, char **av)
// {
// 	t_data	data;
// 	char	**map;

// 	if (ac != 2)
// 		return (ft_putstr_fd("Usage: ./so_long <map_file>\n", 2), 1);
// 	// Initialize everything to NULL
// 	ft_memset(&data, 0, sizeof(t_data));
// 	data.mlx = mlx_init();
// 	if (!data.mlx)
// 		return (ft_putstr_fd("Error: Failed to initialize MiniLibX\n", 2), 1);
// 	map = read_map(av[1]);
// 	if (!map)
// 		return (ft_putstr_fd("Error: Failed to read the map\n", 2), 1);
// 	data.map_data = map;
// 	count_map_width_height(map, &data.map);
// 	if (!validate_map(map) || !check_map_validity(map))
// 		return (free_map(map), 1);
// 	data.win = mlx_new_window(data.mlx, data.map.w * 32, data.map.h * 32,
// 			"GAME");
// 	if (!data.win)
// 	{
// 		free_map(map);
// 		return (ft_putstr_fd("Error: Failed to create window\n", 2), 1);
// 	}
// 	initialize_images(&data);
// 	load_player_textures(&data);
// 	load_player_textures_enemy(&data);
// 	initialize_player(&data, map);
// 	initialize_enemy(&data, map);
// 	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
// 	mlx_hook(data.win, 17, 1L << 5, close_handler, &data);
// 	draw_map(&data, map);
// 	mlx_loop(data.mlx);
// 	cleanup_textures(&data);
// 	free_map(map);
// 	return (0);
// }
int	main(int ac, char **av)
{
	t_data	data;
	char	**map;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./so_long <map_file>\n", 2), 1);
	
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_putstr_fd("Error: Failed to initialize MiniLibX\n", 2), 1);
	
	map = read_map(av[1]);
	if (!map)
		return (ft_putstr_fd("Error: Failed to read the map\n", 2), 1);
	
	data.map_data = map;
	count_map_width_height(map, &data.map);
	
	if (!validate_map(map) || !check_map_validity(map))
		return (free_map(map), 1);
	
	data.win = mlx_new_window(data.mlx, data.map.w * 32, data.map.h * 32, "GAME");
	if (!data.win)
	{
		free_map(map);
		return (ft_putstr_fd("Error: Failed to create window\n", 2), 1);
	}
	
	initialize_images(&data);
	load_player_textures(&data);
	load_player_textures_enemy(&data);
	initialize_player(&data, map);
	initialize_enemy(&data, map);
	
	// Ensure proper event handling
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);   // Key press
	mlx_hook(data.win, 17, 1L << 5, close_handler, &data);   // Window close
	
	draw_map(&data, map);
	mlx_loop(data.mlx);
	
	cleanup_textures(&data);
	free_map(map);
	return (0);
}