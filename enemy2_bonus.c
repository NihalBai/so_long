/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:07:08 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/11 21:54:57 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_enemy(t_data *data, char **map)
{
	int			attempts;
	const int	max = 100;
	int			x;
	int			y;

	attempts = 0;
	data->enemy.current_frame_enemy = 0;
	while (attempts < max)
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

void	load_enemy_textures(t_data *game)
{
	char	*textures[7];
	int		i;

	textures[0] = "textures/1.xpm";
	textures[1] = "textures/2.xpm";
	textures[2] = "textures/3.xpm";
	textures[3] = "textures/4.xpm";
	textures[4] = "textures/5.xpm";
	textures[5] = "textures/6.xpm";
	textures[6] = "textures/7.xpm";
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
		data->enemy.current_frame_enemy = 0;
}

int	game_loop(void *param)
{
	t_data		*data;
	static int	frame_counter;

	frame_counter = 0;
	data = (t_data *)param;
	if (frame_counter++ % 10 == 0)
		animate_enemy(data);
	draw_entities(data);
	return (0);
}
