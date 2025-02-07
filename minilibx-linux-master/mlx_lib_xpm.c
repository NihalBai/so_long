/*
** mlx_xpm.c for minilibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Fri Dec  8 11:07:24 2000 Charlie Root
** Last update Thu Oct  4 16:00:22 2001 Charlie Root
*/


#include	"mlx_int.h"




void		*mlx_int_xpm_f_image(t_xvar *xvar,int *width,int *height,
				     int (*xpm_func)(),void *param)
{
  XImage	*textures1;
  XImage	*textures2;
  t_textures		*im2;
  XpmAttributes	xpm_att;

  xpm_att.visual = xvar->visual;
  xpm_att.colormap = xvar->cmap;
  xpm_att.depth = xvar->depth;
  xpm_att.bitmap_format = ZPixmap;
  xpm_att.valuemask = XpmDepth|XpmBitmapFormat|XpmVisual|XpmColormap;
  if (xpm_func(xvar->display,param,&textures1,&textures2,&xpm_att))
    return ((void *)0);
  if (textures2)
    XDestroyImage(textures2);

  if (!(im2 = (void *)mlx_new_image(xvar,textures1->width,textures1->height)))
    {
      XDestroyImage(textures1);
      return ((void *)0);
    }
  *width = textures1->width;
  *height = textures1->height;
  if (mlx_int_egal_textures(im2->image,textures1))
    {
      bcopy(textures1->data,im2->data,textures1->height*textures1->bytes_per_line);
      XDestroyImage(textures1);
      return (im2);
    }
  if (im2->type==MLX_TYPE_SHM_PIXMAP)
    {
      XFreePixmap(xvar->display,im2->pix);
      im2->pix = XCreatePixmap(xvar->display,xvar->root,
			       *width,*height,xvar->depth);
    }
  if (im2->type>MLX_TYPE_XIMAGE)
    {
      XShmDetach(xvar->display,&(im2->shm));
      shmdt(im2->data);
    }
  XDestroyImage(im2->image);
  im2->image = textures1;
  im2->data = textures1->data;
  im2->type = MLX_TYPE_XIMAGE;
  im2->size_line = textures1->bytes_per_line;
  im2->bpp = textures1->bits_per_pixel;
  return (im2);
}


int	mlx_int_egal_textures(XImage *textures1,XImage *textures2)
{
  if (textures1->width!=textures2->width || textures1->height!=textures2->height ||
      textures1->xoffset!=textures2->xoffset || textures1->format!=textures2->format ||
      textures1->byte_order!=textures2->byte_order ||
      textures1->bitmap_unit!=textures2->bitmap_unit ||
      textures1->bitmap_bit_order!=textures2->bitmap_bit_order ||
      textures1->bitmap_pad!=textures2->bitmap_pad || textures1->depth!=textures2->depth ||
      textures1->bytes_per_line!=textures2->bytes_per_line ||
      textures1->bits_per_pixel!=textures2->bits_per_pixel ||
      textures1->red_mask!=textures2->red_mask || textures1->green_mask!=textures2->green_mask ||
      textures1->blue_mask!=textures2->blue_mask )
    return (0);
  return (1);
}


void	*mlx_xpm_file_to_image(t_xvar *xvar,char *filename,
			       int *width,int *height)
{
  return (mlx_int_xpm_f_image(xvar,width,height,XpmReadFileToImage,filename));
}


void	*mlx_xpm_to_image(t_xvar *xvar,char **data,int *width,int *height)
{
  return (mlx_int_xpm_f_image(xvar,width,height,XpmCreateImageFromData,(void *)data));
}
