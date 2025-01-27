/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:56:32 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/01/27 16:41:36 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux-master/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
// #include "get_next_line.h"
// #include "libft.h"
 
typedef struct s_data
{
	void *mlx;       // MiniLibX instance
	void *win;       // Window instance
	void *img;       // Image instance
	char *addr;      // Image data address
	int bpp;         // Bits per pixel
	int img_width;   // Texture width
	int img_height;  // Texture height
	int line_length; // Line length of the image
	int endian;      // Endianness of the image

	// Image assets
	void *wall_img;    // Wall texture
	void *floor_img;   // Floor texture
	void *player_img;  // Player texture
	void *collect_img; // Collectible texture
	void *exit_img;    // Exit texture
}		t_data;

typedef struct s_map
{
	int w; // Map width (columns)
	int h; // Map height (rows)
}		t_map;

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
int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC key
	{
		mlx_destroy_window(data->mlx, data->win);
		printf("Window closed via ESC key.\n");
		exit(0);
	}
	return (0);
}
int	close_handler(t_data *vars)
{
	printf("Window closed via close button.\n");
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
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "img/Cold.xpm",
			&data->img_width, &data->img_height);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "img/gass.xpm",
			&data->img_width, &data->img_height);
	data->player_img = mlx_xpm_file_to_image(data->mlx, "img/back.xpm",
			&data->img_width, &data->img_height);
	data->collect_img = mlx_xpm_file_to_image(data->mlx, "img/rose.xpm",
			&data->img_width, &data->img_height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "img/exit.xpm",
			&data->img_width, &data->img_height);
	if (!data->wall_img || !data->floor_img || !data->player_img
		|| !data->collect_img || !data->exit_img)
	{
		printf("Error: Failed to load one or more XPM images.\n");
		exit(EXIT_FAILURE);
	}
}
void	*choose_img(t_data *data, char tile)
{
	if (tile == '1')
		return (data->wall_img);
	if (tile == '0')
		return (data->floor_img);
	if (tile == 'P')
		return (data->player_img);
	if (tile == 'C')
		return (data->collect_img);
	if (tile == 'E')
		return (data->exit_img);
	return (NULL);
}

void	draw_map(t_data *data, char **map)
{
	void	*current_img;
	int(x), (y), (i), (j);
    
	y = 0;
	i = 0;
	while (map[y] != NULL)
	{
		x = 0;
		j = 0;
		while (map[y][x] != '\0')
		{
			current_img = choose_img(data, map[y][x]);
			if (current_img)
				mlx_put_image_to_window(data->mlx, data->win, current_img, j,
					i);
			j += 32;
			x++;
		}
		y++;
		i += 32;
	}
}

// char **read_map(const char *file)
// {
//     int fd;
//     char *line;
//     char **map;
//     size_t row_count = 0;
//     size_t i = 0;

//     // Open the map file
//     fd = open(file, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error: Could not open map file");
//         return (NULL);
//     }

//     // Count the number of lines in the map file
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         row_count++;
//         free(line);
//     }
//     close(fd);

//     // Allocate memory for the map (including NULL terminator)
//     map = (char **)malloc((row_count + 1) * sizeof(char *));
//     if (!map)
//         return (NULL);

//     // Read the map lines into the array
//     fd = open(file, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error: Could not reopen map file");
//         free(map);
//         return (NULL);
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         map[i++] = ft_strdup(line); // Duplicate each line
//         free(line);                 // Free the line returned by GNL
//     }
//     map[i] = NULL; // NULL-terminate the map
//     close(fd);

//     return (map);
// }
#include <stdio.h>

int validate_map(char **map)
{
    int i = 0;
    int p_count = 0, e_count = 0, c_count = 0;

    while (map[i])
    {
        int j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
                p_count++;
            else if (map[i][j] == 'E')
                e_count++;
            else if (map[i][j] == 'C')
                c_count++;
            j++;
        }
        i++;
    }

    // Validate that there is exactly one P, one E, and at least five C's
    if (p_count != 1 || e_count != 1 || c_count < 1)
    {
        printf("Error: Invalid map! Ensure there is 1 player (P), 1 exit (E), and at least 1 collectible (C).\n");
        return 0;
    }
    return 1;
}


void flood_fill(char **map, int x, int y, int *visited)
{
    if (x < 0 || y < 0 || !map[y] || map[y][x] == '1' || visited[y * 100 + x]) // assuming map width of 100
        return;

    visited[y * 100 + x] = 1;
    
    // Recursively visit neighboring cells
    flood_fill(map, x + 1, y, visited); // Right
    flood_fill(map, x - 1, y, visited); // Left
    flood_fill(map, x, y + 1, visited); // Down
    flood_fill(map, x, y - 1, visited); // Up
}

int check_map_validity(char **map)
{
    int i = 0;
    int start_x = -1, start_y = -1;
    int visited[10000] = {0}; // Array for marking visited cells (assuming a max map size of 100x100)

    // Find the player start position
    while (map[i])
    {
        int j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                start_x = j;
                start_y = i;
                break;
            }
            j++;
        }
        if (start_x != -1)
            break;
        i++;
    }

    if (start_x == -1)
    {
        printf("Error: No player (P) found on the map.\n");
        return 0;
    }

    // Perform flood fill starting from the player position
    flood_fill(map, start_x, start_y, visited);

    // Check if all empty spaces (0's) are reachable
    i = 0;
    while (map[i])
    {
        int j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0' && !visited[i * 100 + j])
            {
                printf("Error: Map is not fully connected.\n");
                return 0;
            }
            j++;
        }
        i++;
    }

    return 1; // If no issues, the map is valid
}

int	main()
{
	t_data	data;
	t_map	map_info;
    // char **map;
    //  if (ac != 2)
    // {
    //     ft_putstr_fd("Usage: ./program <map_file>\n", 2);
    //     return (1);
    // }
	char *map[] = {
    "111111111111111",
    "1P0000000000001",
    "101C0000000C101",
    "101000000001011",
    "101010000C01C01",
    "10001C000001001",
    "101010000001001",
    "101E00000000101",
    "101000000000001",
    "1C10000C0000001",
    "111111111111111",
    NULL
};

	count_map_width_height(map, &map_info);
	// Initialize MiniLibX
	data.mlx = mlx_init();
	initialize_images(&data);
	if (!data.mlx)
	{
		printf("Error: Failed to initialize MiniLibX\n");
		return (1);
	}
    // //  map = read_map(av[1]);
    //  if (!map)
    // {
    //     ft_putstr_fd("Error: Failed to read the map\n", 2);
    //     return (1);
    // }
    if (!validate_map(map) || !check_map_validity(map))
        {return 1;}
	data.win = mlx_new_window(data.mlx, map_info.w * 32, map_info.h * 32,
			"Full-Screen Map");
	if (!data.win)
	{
		printf("Error: Failed to create window\n");
		return (1);
	}
	// Draw the map to fill the entire window
	draw_map(&data, map);
	// Set up key press and window close event hooks
	mlx_hook(data.win, 2, 1L << 0, key_handler, &data);
	mlx_hook(data.win, 17, 1L << 5, close_handler, &data);

	mlx_loop(data.mlx);
	return (0);
}
