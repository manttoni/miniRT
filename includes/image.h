#ifndef IMAGE_H
# define IMAGE_H

# include "./data.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct	s_image
{
	mlx_image_t	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		focal_len;
}	t_image;

/* Image */
void		color_pixel(t_image *image, uint32_t pixel_color, int x, int y);

#endif
