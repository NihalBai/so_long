/*
** mlx_destroy_image.c for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Tue Mar 12 10:25:15 2002 Charlie Root
** Last update Tue May 15 16:45:54 2007 Olivier Crouzet
*/


#include	"mlx_int.h"


int	mlx_destroy_image(t_xvar *xvar, t_textures *textures)
{
  if (textures->type == MLX_TYPE_SHM_PIXMAP ||
      textures->type == MLX_TYPE_SHM)
    {
      XShmDetach(xvar->display, &(textures->shm));
      shmdt(textures->shm.shmaddr);
      /* shmctl IPC_RMID already done */
    }
  XDestroyImage(textures->image);  /* For image & shm-image. Also free textures->data */
  XFreePixmap(xvar->display, textures->pix);
  if (textures->gc)
    XFreeGC(xvar->display, textures->gc);
  free(textures);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
