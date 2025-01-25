#include "../includes/minirt.h"
#include "../includes/defines.h"


void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	int	pixel_index;

	pixel_index = y * X + x;
	((uint32_t *)(image->pixels))[pixel_index] = pixel_color;

}
