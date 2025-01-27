#include "./minilibx-linux-master/mlx.h"
#include <stdio.h>
#include <unistd.h>


#include <stdlib.h>

typedef struct s_vars {
    void    *mlx;
    void    *win;
    void    *img;          // Texture image
    int     img_width;     // Texture width
    int     img_height;    // Texture height
    int     mouse_inside;  // Track whether the mouse is inside the window
}               t_vars;

// Key press event handler
int key_handler(int keycode, t_vars *vars)
{
    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307) // 65307 is the keycode for the ESC key
    {
        mlx_destroy_window(vars->mlx, vars->win);
        printf("Window closed via ESC key.\n");
        exit(0);
    }
    return (0);
}

int main(void)
{
    t_vars vars;

    // Initialize MiniLibX
    vars.mlx = mlx_init();
    if (!vars.mlx)
    {
        printf("Error: Failed to initialize MiniLibX\n");
        return (1);
    }

    // Create a window
    vars.win = mlx_new_window(vars.mlx, 1200, 1200, "Image Display Example");
    if (!vars.win)
    {
        printf("Error: Failed to create window\n");
        return (1);
    }

    // Load the image
    char *relative_path = "./gojo.xpm"; // Path to your XPM image
    vars.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &vars.img_width, &vars.img_height);
    if (!vars.img)
    {
        printf("Error: Failed to load image\n");
        return (1);
    }
	int i = 0;
    // Display the image in the window
	

	mlx_loop_hook(vars.mlx,  , )
	

    // Set up key press event hook
    mlx_hook(vars.win, 2, 1L << 0, key_handler, &vars);

    // Start the MiniLibX event loop
    mlx_loop(vars.mlx);

    return (0);
}
