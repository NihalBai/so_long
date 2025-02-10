/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:14:58 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/10 01:18:09 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static unsigned long	seed = 1;

int	ft_rand(void)
{
	unsigned long	a;
	unsigned long	c;

	a = 1103515245;
	c = 12345;
	unsigned long m = 2147483648; // 2^31
	seed = (a * seed + c) % m;
	return (int)(seed % (INT_MAX + 1UL));
}

void	ft_srand(unsigned int new_seed)
{
	seed = new_seed;
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

int	close_handler(t_data *data)
{
	if (win)
		mlx_string_put(data->mlx, data->win, 50, 50, 0x00FF00, "You Win!");
	else
		mlx_string_put(data->mlx, data->win, 50, 50, 0xFF0000, "Game Over!");
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
