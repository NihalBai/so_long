#include "./minilibx-linux-master/mlx.h"
#include <stdio.h>

// #include <stdio.h>

// typedef struct s_data {
//     void    *img;
//     char    *addr;
//     int     bits_per_pixel;
//     int     line_length;
//     int     endian;
// }               t_data;

// // Function to create a color in ARGB format
// int create_trgb(int t, int r, int g, int b)
// {
//     return (t << 24 | r << 16 | g << 8 | b);
// }

// // Function to add shading to a color
// int add_shade(double distance, int color)
// {
//     int t = (color >> 24) & 0xFF;
//     int r = (color >> 16) & 0xFF;
//     int g = (color >> 8) & 0xFF;
//     int b = color & 0xFF;

//     r = (int)(r * (1 - distance));
//     g = (int)(g * (1 - distance));
//     b = (int)(b * (1 - distance));

//     return (t << 24 | r << 16 | g << 8 | b);
// }

// // Function to get the opposite (inverted) color
// int get_opposite(int color)
// {
//     int t = (color >> 24) & 0xFF;
//     int r = (color >> 16) & 0xFF;
//     int g = (color >> 8) & 0xFF;
//     int b = color & 0xFF;

//     r = 255 - r;
//     g = 255 - g;
//     b = 255 - b;

//     return (t << 24 | r << 16 | g << 8 | b);
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     time_t  key_pressed_time; // Track when a key is pressed
//     int     mouse_inside;     // Track whether the mouse is inside the window
// }               t_vars;

// // Key press event handler
// int key_handler(int keycode, t_vars *vars)
// {
//     printf("Key pressed: %d\n", keycode);
//     if (keycode == 65307) // 65307 is the keycode for the ESC key
//     {
//         mlx_destroy_window(vars->mlx, vars->win);
//         printf("Window closed via ESC key.\n");
//         exit(0);
//     }
//     vars->key_pressed_time = time(NULL); // Record the time when the key is pressed
//     return (0);
// }

// // Key release event handler
// int key_release_handler(int keycode, t_vars *vars)
// {
//     printf("Key released: %d\n", keycode);
//     time_t current_time = time(NULL);
//     if (current_time - vars->key_pressed_time > 2) // Check if key was pressed for more than 2 seconds
//     {
//         printf("Key was pressed for more than 2 seconds.\n");
//     }
//     return (0);
// }

// // Window close event handlert_vars
// int close_handler(t_vars *vars)
// {
//     printf("Window closed via close button.\n");
//     mlx_destroy_window(vars->mlx, vars->win);
//     exit(0);
// }

// // Mouse motion event handler (simulate mouse enter/leave)
// int mouse_motion_handler(int x, int y, t_vars *vars)
// {t_vars
//     (void)x; // Unused parameter
//     (void)y; // Unused parameter
//     if (!vars->mouse_inside)
//     {
//         printf("Hello! Mouse entered the window.\n");
//         vars->mouse_inside = 1;
//     }
// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     time_t  key_pressed_time; // Track when a key is pressed
//     int     mouse_inside;     // Track whether the mouse is inside the window
// }               t_vars;

// // Key press event handler
//         printf("Bye! Mouse left the window.\n");
//         vars->mouse_inside = 0;
//     }
//     return (0);
// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     time_t  key_pressed_time; // Track when a key is pressed
//     int     mouse_inside;     // Track whether the mouse is inside the window
// }               t_vars;

// // Key press event handler
// }

// int main(void)
// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     time_t  key_pressed_time; // Track when a key is pressed
//     int     mouse_inside;     // Track whether the mouse is inside the window
// }               t_vars;

// // Key press event handler
// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     time_t  key_pressed_time; // Track when a key is pressed
//     int     mouse_inside;     // Track whether the mouse is inside the window
// }               t_vars;

// // Key press event handler

//     // Initialize MiniLibX
//     vars.mlx = mlx_init();
//     if (!vars.mlx)
//     {
//         printf("Error: Failed to initialize MiniLibX\n");
//         return (1);
//     }

//     // Create a window
//     vars.win = mlx_new_window(vars.mlx, 500, 500, "Event Handling Example");
//     if (!vars.win)
//     {
//         printf("Error: Failed to create window\n");
//         return (1);
//     }

//     // Initialize mouse trackingt_vars
//     vars.mouse_inside = 0;

//     // Set up key press event hook
//     mlx_hook(vars.win, 2, 1L << 0, key_handler, &vars);
//     printf("Key press hook set up.\n");

//     // Set up key release event hook
//     mlx_hook(vars.win, 3, 1L << 1, key_release_handler, &vars);
//     printf("Key release hook set up.\n");

//     // Set up window close event hook
//     mlx_hook(vars.win, 17, 1L << 5, close_handler, &vars);
//     printf("Window close hook set up.\n");

//     // Set up mouse motion event hook
//     mlx_hook(vars.win, 4, 1L<<4, mouse_motion_handler, &vars);
//     printf("Mouse motion hook set up.\n");

//     // Set up focus out event hook (simulate mouse leave)
//     mlx_hook(vars.win, 9, 0, focus_out_handler, &vars);
//     printf("Focus out hook set up.\n");

//     // Start the MiniLibX event loop
//     printf("Entering MiniLibX event loop.\n");
//     mlx_loop(vars.mlx);

//     return (0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    
}               t_data;

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

// Function to interpolate between two colors
int interpolate_color(int color1, int color2, double t)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r = (int)(r1 + (r2 - r1) * t);
    int g = (int)(g1 + (g2 - g1) * t);
    int b = (int)(b1 + (b2 - b1) * t);

    return create_trgb(0, r, g, b);
}

// Function to update the rainbow color
void update_rainbow(t_data *data)
{
    double t = fmod(data->time, 3.0) / 3.0; // Cycle every 3 seconds

    int color1, color2;
    if (t < 1.0 / 3.0) {
        color1 = create_trgb(0, 255, 0, 0);   // Red
        color2 = create_trgb(0, 0, 255, 0);   // Green
        t = t * 3.0;
    } else if (t < 2.0 / 3.0) {
        color1 = create_trgb(0, 0, 255, 0);   // Green
        color2 = create_trgb(0, 0, 0, 255);   // Blue
        t = (t - 1.0 / 3.0) * 3.0;
    } else {
        color1 = create_trgb(0, 0, 0, 255);   // Blue
        color2 = create_trgb(0, 255, 0, 0);   // Red
        t = (t - 2.0 / 3.0) * 3.0;
    }

    data->color = interpolate_color(color1, color2, t);
}

// Function to render the rainbow
void render_rainbow(t_data *data)
{
    int width = 800;
    int height = 600;

    // Fill the image with the current color
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel = y * data->line_length + x * (data->bits_per_pixel / 8);
            *(int *)(data->addr + pixel) = data->color;
        }
    }

    // Display the image in the window
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

// Function to handle key presses
int key_handler(int keycode, t_data *data)
{
    if (keycode == 65307) // ESC key
    {
        mlx_destroy_window(data->mlx, data->win);
        printf("Window closed via ESC key.\n");
        exit(0);
    }
    return (0);
}

// Main loop function
int loop_handler(t_data *data)
{
    data->time += 0.01; // Increment time for color interpolation
    update_rainbow(data);
    render_rainbow(data);
    return (0);
}

int main(void)
{
    t_data data; mlx_hook(vars.win, 2, 1L << 0, key_handler, &vars);
    // Initialize time and color
    data.time = 0.0;
    data.color = create_trgb(0, 255, 0, 0); // Start with red

    // Set up key press event hook
    mlx_hook(data.win, 2, 1L << 0, key_handler, &data);

    // Set up loop hook for continuous rendering
    mlx_loop_hook(data.mlx, loop_handler, &data);

    // Start the MiniLibX event loop
    mlx_loop(data.mlx);

    return (0);
}


// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     void    *img;          // Texture image
//     int     img_width;     // Texture width
//     int     img_height;    // Texture height
//     int     mouse_inside;  // Track whether the mouse is inside the window
// }               t_vars;

// // Function to handle key presses
// int key_handler(int keycode, t_vars *vars)
// {
//     printf("Key pressed: %d\n", keycode);
//     if (keycode == 65307) // 65307 is the keycode for the ESC key
//     {
//         mlx_destroy_window(vars->mlx, vars->win);
//         printf("Window closed via ESC key.\n");
//         exit(0);
//     }
//     return (0);
// }

// // Function to handle window close
// int close_handler(t_vars *vars)
// {
//     mlx_destroy_window(vars->mlx, vars->win);
//     printf("Window closed via close button.\n");
//     exit(0);
// }

// // Function to tile the texture across the window
// void tile_texture(t_vars *vars)
// {
//     int win_width;
//     int win_height;

//     // Get window dimensions
//     mlx_get_screen_size(vars->mlx, &win_width, &win_height);

//     // Tile the texture across the window
//     for (int y = 0; y < win_height; y += vars->img_height)
//     {
//         for (int x = 0; x < win_width; x += vars->img_width)
//         {
//             mlx_put_image_to_window(vars->mlx, vars->win, vars->img, x, y);
//         }
//     }
// }

// // Function to handle window expose event (redraw when resized)
// int expose_handler(t_vars *vars)
// {
//     tile_texture(vars);
//     return (0);
// }

// // Function to handle mouse enter event
// int mouse_enter_handler(t_vars *vars)
// {
//     if (!vars->mouse_inside)
//     {
//         printf("Hello! Mouse entered the window.\n");
//         vars->mouse_inside = 1;
//     }
//     return (0);
// }

// // Function to handle mouse leave event
// int mouse_leave_handler(t_vars *vars)
// {
//     if (vars->mouse_inside)
//     {
//         printf("Bye! Mouse left the window.\n");
//         vars->mouse_inside = 0;
//     }
//     return (0);
// }

// int main(void)
// {
//     t_vars  vars;
//     char    *relative_path = "./test.xpm"; // Path to your texture file

//     // Initialize MiniLibX
//     vars.mlx = mlx_init();
//     if (!vars.mlx)
//     {
//         printf("Error: Failed to initialize MiniLibX\n");
//         return (1);
//     }

//     // Load the texture from the XPM file
//     vars.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &vars.img_width, &vars.img_height);
//     if (!vars.img)
//     {
//         printf("Error: Failed to load texture from %s\n", relative_path);
//         return (1);
//     }

//     // Create a window
//     int win_width = 800; // Default window width
//     int win_height = 600; // Default window height
//     vars.win = mlx_new_window(vars.mlx, win_width, win_height, "Tiled Texture");
//     if (!vars.win)
//     {
//         printf("Error: Failed to create window\n");
//         return (1);
//     }

//     // Initialize mouse tracking
//     vars.mouse_inside = 0;

//     // Tile the texture across the window
//     tile_texture(&vars);

//     // Set up key press event hook
//     mlx_hook(vars.win, 2, 1L << 0, key_handler, &vars);

//     // Set up window close event hook
//     mlx_hook(vars.win, 17, 0, close_handler, &vars);

//     // Set up expose event hook (redraw when resized)
//     mlx_expose_hook(vars.win, expose_handler, &vars);

//     // Set up mouse enter event hook
//     mlx_hook(vars.win, 7, 0, mouse_enter_handler, &vars);

//     // Set up mouse leave event hook
//     mlx_hook(vars.win, 8, 0, mouse_leave_handler, &vars);

//     // Start the MiniLibX event loop
//     mlx_loop(vars.mlx);

//     return (0);
// }