/*
** mlx_new_image.c for MiniLibX in raytraceur
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Aug 14 15:29:14 2000 Charlie Root
** Last update Wed May 25 16:46:31 2011 Olivier Crouzet
*/




#include	"mlx_int.h"

/*
** To handle X errors
*/

#define	X_ShmAttach	1

int	mlx_X_error;

int	shm_att_pb(Display *d,XErrorEvent *ev)
{
  if (ev->request_code==146 && ev->minor_code==X_ShmAttach)
    write(2,WARN_SHM_ATTACH,strlen(WARN_SHM_ATTACH));
  mlx_X_error = 1;
}


/*
**  Data malloc :  width+32 ( bitmap_pad=32 ),    *4 = *32 / 8bit
*/


void	*mlx_int_new_xshm_image(t_xvar *xvar,int width,int height,int format)
{
  t_textures	*textures;
  int	(*save_handler)();

  if (!(textures = malloc(sizeof(*textures))))
    return ((void *)0);
  bzero(textures,sizeof(*textures));
  textures->data = 0;
  textures->image = XShmCreateImage(xvar->display,xvar->visual,xvar->depth,
			       format,textures->data,&(textures->shm),width,height);
  if (!textures->image)
    {
      free(textures);
      return ((void *)0);
    }
  textures->width = width;
  textures->height = height;
  textures->size_line = textures->image->bytes_per_line;
  textures->bpp = textures->image->bits_per_pixel;
  textures->format = format;
  textures->shm.shmid = shmget(IPC_PRIVATE,(width+32)*height*4,IPC_CREAT|0777);
  if (textures->shm.shmid==-1)
    {
      XDestroyImage(textures->image);
      free(textures);
      return ((void *)0);
    }
  textures->data = textures->shm.shmaddr = textures->image->data = shmat(textures->shm.shmid,0,0);
  if (textures->data==(void *)-1)
    {
      shmctl(textures->shm.shmid,IPC_RMID,0);
      XDestroyImage(textures->image);
      free(textures);
      return ((void *)0);
    }
  textures->shm.readOnly = False;
  mlx_X_error = 0;
  save_handler = XSetErrorHandler(shm_att_pb);
  if (!XShmAttach(xvar->display,&(textures->shm)) ||
      0&XSync(xvar->display,False) || mlx_X_error)
    {
      XSetErrorHandler(save_handler);
      shmdt(textures->data);
      shmctl(textures->shm.shmid,IPC_RMID,0);
      XDestroyImage(textures->image);
      free(textures);
      return ((void *)0);
    }
  XSetErrorHandler(save_handler);
  shmctl(textures->shm.shmid,IPC_RMID,0);
  if (xvar->pshm_format==format)
    {
      textures->pix = XShmCreatePixmap(xvar->display,xvar->root,textures->shm.shmaddr,
				  &(textures->shm),width,height,xvar->depth);
      textures->type = MLX_TYPE_SHM_PIXMAP;
    }
  else
    {
      textures->pix = XCreatePixmap(xvar->display,xvar->root,
			       width,height,xvar->depth);
      textures->type = MLX_TYPE_SHM;
    }
  if (xvar->do_flush)
    XFlush(xvar->display);
  return (textures);
}



void	*mlx_int_new_image(t_xvar *xvar,int width, int height,int format)
{
  t_textures	*textures;

  if (!(textures = malloc(sizeof(*textures))))
    return ((void *)0);
  if (!(textures->data = malloc((width+32)*height*4)))
  {
    free(textures);
    return ((void *)0);
  }
  bzero(textures->data,(width+32)*height*4);
  textures->image = XCreateImage(xvar->display,xvar->visual,xvar->depth,format,0,
			    textures->data,width,height,32,0);
  if (!textures->image)
    {
      free(textures->data);
      free(textures);
      return ((void *)0);
    }
  textures->gc = 0;
  textures->size_line = textures->image->bytes_per_line;
  textures->bpp = textures->image->bits_per_pixel;
  textures->width = width;
  textures->height = height;
  textures->pix = XCreatePixmap(xvar->display,xvar->root,width,height,xvar->depth);
  textures->format = format;
  textures->type = MLX_TYPE_XIMAGE;
  if (xvar->do_flush)
    XFlush(xvar->display);
  return (textures);
}


void	*mlx_new_image(t_xvar *xvar,int width, int height)
{
  t_textures	*textures;

  if (xvar->use_xshm)
    if (textures = mlx_int_new_xshm_image(xvar,width,height,ZPixmap))
      return (textures);
  return (mlx_int_new_image(xvar,width,height,ZPixmap));
}

void	*mlx_new_image2(t_xvar *xvar,int width, int height)
{
  t_textures	*textures;

  if (xvar->use_xshm)
    if (textures = mlx_int_new_xshm_image(xvar,width,height,XYPixmap))
      return (textures);
  return (mlx_int_new_image(xvar,width,height,XYPixmap));
}
