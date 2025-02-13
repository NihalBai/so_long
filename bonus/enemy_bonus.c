/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:06:47 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/11 22:02:55 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			{
				x[*count] = j;
				y[*count] = i;
				(*count)++;
			}
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

static void	update_enemy_position(t_data *data, int new_x, int new_y)
{
	data->map_data[data->enemy.y][data->enemy.x] = '0';
	data->enemy.x = new_x;
	data->enemy.y = new_y;
	data->map_data[new_y][new_x] = 'M';
	data->enemy.current_frame_enemy = 0;
}

void	move_enemy(t_data *data)
{
	static int	last[2] = {-1, -1};
	int			*x;
	int			*y;
	int			count;
	int			r;

	count = 0;
	get_empty_spaces(data, &x, &y, &count);
	if (count > 0)
	{
		r = ft_rand() % count;
		if (x[r] != last[0] || y[r] != last[1])
			update_enemy_position(data, x[r], y[r]);
		else
			animate_enemy(data);
		last[0] = data->enemy.x;
		last[1] = data->enemy.y;
	}
	free(x);
	free(y);
}
