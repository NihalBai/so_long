/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:06:47 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/08 02:16:14 by nbaidaou         ###   ########.fr       */
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
		y = ft_rand() % data->map.h;
		x = ft_rand() % data->map.w;
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
	static int	last_x = -1, last_y = -1;
	int			new_x;
	int			new_y;

	int r, *x, *y, count = 0;
	get_empty_spaces(data, &x, &y, &count);
	if (count > 0)
	{
		r = ft_rand() % count;
		new_x = x[r];
		new_y = y[r];
		if (new_x != last_x || new_y != last_y)
		{
			data->map_data[data->enemy.y][data->enemy.x] = '0';
			data->enemy.x = new_x;
			data->enemy.y = new_y;
			data->map_data[new_y][new_x] = 'M';
			data->enemy.current_frame_enemy = 0;
		}
		else
			animate_enemy(data);
		last_x = data->enemy.x;
		last_y = data->enemy.y;
	}
	free(x);
	free(y);
}

void	load_enemy_textures(t_data *game)
{
	char	*textures[7] = {"textures/1.xpm", "textures/2.xpm",
			"textures/3.xpm", "textures/4.xpm", "textures/5.xpm",
			"textures/6.xpm", "textures/7.xpm"};
	int		i;

	i = 0;
	while (i < 7)
	{
		game->enemy.textures_enemy[i] = mlx_xpm_file_to_image(game->mlx,
				textures[i], &game->textures_width, &game->textures_height);
		if (!game->enemy.textures_enemy[i])
			ft_putstr_fd("Error loading enemy texture!\n", 2);
		i++;
	}
}

void	animate_enemy(t_data *data)
{
	int	total_frames;

	total_frames = 4;
	data->enemy.current_frame_enemy++;
	if (data->enemy.current_frame_enemy >= total_frames)
	{
		data->enemy.current_frame_enemy = 0;
	}
}

int	game_loop(void *param)
{
	t_data		*data;
	static int	frame_counter = 0;

	data = (t_data *)param;
	if (frame_counter++ % 10 == 0)
	{
		animate_enemy(data);
	}
	draw_entities(data);
	return (0);
}
