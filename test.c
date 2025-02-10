#include "a.h"

int close_handler(t_data *vars)
{
    if (vars->wall_textures)
        mlx_destroy_image(vars->mlx, vars->wall_textures);
    if (vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    if (vars->mlx)
    {
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
    }
    free(vars);
    exit(0);
    return (0);
}

int ESC(int keycode,t_data *vars)
{
    if (keycode == 65307)
	{
		close_handler(vars);
	}
    return (0);
}
int main()
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
    {
        printf("Error: Failed to allocate memory for data\n");
        return (1);
    }

    data->mlx = mlx_init();
    if (!data->mlx)
    {
        printf("Error: Failed to initialize MiniLibX\n");
        free(data);
        return (1);
    }

    data->win = mlx_new_window(data->mlx, 500, 500, "test");
    if (!data->win)
    {
        printf("Error: Failed to create window\n");
        free(data->mlx); // Free MLX instance if window creation fails
        free(data);
        return (1);
    }

	data->wall_textures = mlx_xpm_file_to_image(data->mlx, "textures/Cold.xpm",
        &data->textures_width, &data->textures_height);
	if (!data->wall_textures)
	{
		printf("Error: Failed to load texture\n");
		close_handler(data);
	}


	mlx_hook(data->win, 17, 1L << 5, close_handler, data);

	mlx_hook(data->win, 2, 1L << 0, ESC, data);
    mlx_loop(data->mlx);

	mlx_destroy_image(data->mlx, data->wall_textures);

    mlx_destroy_window(data->mlx, data->win);
	 mlx_destroy_display(data->mlx);
    free(data->mlx);
    free(data);

    return (0);
}
