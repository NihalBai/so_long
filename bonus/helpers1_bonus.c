/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:05:31 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/13 01:29:21 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_last_valid_line(char **map)
{
	int	i;
	int	last_valid_line;

	i = -1;
	last_valid_line = -1;
	while (map[++i])
	{
		if (map[i][0] != '\0')
			last_valid_line = i;
	}
	return (last_valid_line);
}

int	count_map_elements(char **map, int last_valid_line, t_map_counts *counts)
{
	int	i;
	int	j;

	counts->p = 0;
	counts->e = 0;
	counts->c = 0;
	i = -1;
	while (++i <= last_valid_line)
	{
		if ((int)ft_strlen(map[i]) != (int)ft_strlen(map[0]))
			return (ft_putstr_fd("Error: Map must be rectangular.\n", 2), 0);
		j = -1;
		while (map[i][++j])
		{
			counts->p += (map[i][j] == 'P');
			counts->e += (map[i][j] == 'E');
			counts->c += (map[i][j] == 'C');
		}
	}
	return (1);
}

void	find_map_bounds(char **map, int *first, int *last)
{
	int	i;

	*first = -1;
	*last = -1;
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '\0')
		{
			if (*first == -1)
				*first = i;
			*last = i;
		}
		i++;
	}
}

void	counter(t_data *data, int c)
{
	int		color;
	int		x;
	int		y;
	char	*msg;
	char	*full_msg;

	color = 0xFAB7BA;
	msg = ft_itoa(c);
	if (!msg)
		return ;
	full_msg = ft_strjoin("Total moves: ", msg);
	free(msg);
	if (!full_msg)
	{
		return ;
	}
	x = 10;
	y = 20;
	mlx_string_put(data->mlx, data->win, x, y, color, full_msg);
	mlx_do_sync(data->mlx);
	free(full_msg);
}
