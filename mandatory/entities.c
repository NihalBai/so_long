/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:03:40 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/13 22:26:48 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_texture_group(void *mlx, void *textures[4][2])
{
	int	i;
	int	j;

	if (!mlx || !textures)
		return ;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 2)
		{
			if (textures[i][j])
			{
				mlx_destroy_image(mlx, textures[i][j]);
			}
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
	if (data->win_texture)
		mlx_destroy_image(data->mlx, data->win_texture);
	if (data->lose_texture)
		mlx_destroy_image(data->mlx, data->lose_texture);
}

void	draw_entities(t_data *data)
{
	void	*player_tex;

	player_tex = data->player.textures[data->player.direction]
	[data->player.current_frame];
	if (player_tex && !data->game_won)
		mlx_put_image_to_window(data->mlx, data->win, player_tex, data->player.x
			* 32, data->player.y * 32);
}

void	cleanup_textures(t_data *data)
{
	destroy_texture_group(data->mlx, data->player.textures);
	destroy_single_textures(data);
}
