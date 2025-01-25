#ifndef IMAGE_H
# define IMAGE_H

# include "./data.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

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
void		color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y);
t_color		decompose_color(uint32_t color);
uint32_t	recompose_color(t_color color);

#endif
