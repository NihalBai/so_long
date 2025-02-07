/*
** mlx_put_image_to_window.c for MiniLibX in raytraceur
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Aug 14 15:55:49 2000 Charlie Root
** Last update Sun Oct  2 09:53:00 2005 Olivier Crouzet
*/



#include	"mlx_int.h"


int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_textures *textures,
				int x,int y)
{
  GC	gc;

  gc = win->gc;
  if (textures->gc)
    {
      gc = textures->gc;
      XSetClipOrigin(xvar->display, gc, x, y);
    }
  if (textures->type==MLX_TYPE_SHM)
    XShmPutImage(xvar->display,textures->pix, win->gc, textures->image,0,0,0,0,
		 textures->width,textures->height,False);
  if (textures->type==MLX_TYPE_XIMAGE)
    XPutImage(xvar->display,textures->pix, win->gc, textures->image,0,0,0,0,
	      textures->width,textures->height);
  XCopyArea(xvar->display,textures->pix,win->window, gc,
	    0,0,textures->width,textures->height,x,y);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
