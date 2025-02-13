/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:14:58 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/13 22:13:59 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	close_handler(t_data *data)
{
	cleanup_textures(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_map(data->map_data);
	exit(0);
	return (0);
}

void	win_lose(t_data *data, int win)
{
	int		color;
	int		x;
	int		y;
	char	*msg;

	if (win)
	{
		color = 0x00FF00;
		msg = "YOU WIN!";
	}
	else
	{
		color = 0xFF0000;
		msg = "GAME OVER!";
	}
	x = (data->map.w * 32) / 2 - 50;
	y = (data->map.h * 32) / 2 - 20;
	mlx_string_put(data->mlx, data->win, x, y, color, msg);
	mlx_do_sync(data->mlx);
	sleep(2);
}
