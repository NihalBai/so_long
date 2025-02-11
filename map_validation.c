/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:18:26 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/11 16:22:45 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(char **map)
{
	int	i;
	int	j;
	int	p;
	int	e;
	int	c;

	i = -1;
	p = 0;
	e = 0;
	c = 0;
	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) != (int)ft_strlen(map[0]))
			return (ft_putstr_fd("Error: Map must be rectangular.\n", 2), 0);
		j = -1;
		while (map[i][++j])
		{
			p += (map[i][j] == 'P');
			e += (map[i][j] == 'E');
			c += (map[i][j] == 'C');
		}
	}
	if (p != 1 || e != 1 || c < 1)
		return (ft_putstr_fd("Error: Invalid map! Must have 1P,1E,≥1C\n", 2), 0);
	return (1);
}

void	flood_fill(char **map, int x, int y, int *visited)
{
	if (x < 0 || y < 0 || !map[y] || map[y][x] == '1' || visited[y * 100 + x])
		return ;
	visited[y * 100 + x] = 1;
	flood_fill(map, x + 1, y, visited);
	flood_fill(map, x - 1, y, visited);
	flood_fill(map, x, y + 1, visited);
	flood_fill(map, x, y - 1, visited);
}

int	find_player(char **map, int *start_x, int *start_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*start_x = j;
				*start_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error: No player (P) found on the map.\n", 2);
	return (0);
}

int	check_map_fully_connected(char **map, int *visited)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'C' || map[i][j] == 'E') && !visited[i * 100 + j])
			{
				ft_putstr_fd("Error: Map is not fully connected.\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_validity(char **map)
{
	int	start_x;
	int	start_y;
	int	visited[100000];

	ft_bzero(visited, sizeof(visited));
	start_x = -1;
	start_y = -1;
	if (!find_player(map, &start_x, &start_y))
		return (0);
	flood_fill(map, start_x, start_y, visited);
	return (check_map_fully_connected(map, visited));
}
