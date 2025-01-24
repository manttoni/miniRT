#include "../includes/minirt.h"



void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	int	pixel_index;

	// if (x < 0 || x >= X || y < 0 || y >= 0)
	// 	return ;
	pixel_index = y * X + x;
	((uint32_t *)(image->pixels))[pixel_index] = pixel_color;

}
