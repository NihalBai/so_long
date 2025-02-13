/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:54 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/11 16:35:27 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_data *data, char **map)
{
	void	*current_textures;
	int		x;
	int		y;

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
	if (!data->game_lost)
		draw_entities(data);
}

int	count_rows(int fd)
{
	int		row_count;
	char	*line;

	row_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		row_count++;
		free(line);
	}
	return (row_count);
}

char	**fill_map(int fd, size_t row_count)
{
	char	**map;
	char	*line;
	size_t	i;
	char	*trimmed_line;

	map = (char **)malloc((row_count + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, "\n");
		map[i++] = ft_strdup(trimmed_line);
		free(trimmed_line);
		free(line);
	}
	map[i] = NULL;
	return (map);
}

char	**read_map(const char *file)
{
	int		fd;
	char	**map;
	int		row_count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Could not open map file\n", 2), NULL);
	row_count = count_rows(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Could not reopen map file\n", 2), NULL);
	map = fill_map(fd, row_count);
	close(fd);
	return (map);
}
