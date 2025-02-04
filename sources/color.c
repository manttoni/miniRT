
#include "../includes/minirt.h"

int	little_big_endian(void)
{
	int		endian;
	int16_t	x;

	x = 0x0001;
	endian = (*((int8_t *)(&x)) == 0x01);
	return (endian);
}

void	base_pixel(uint8_t *buffer, int colour, int alpha)
{
	if (little_big_endian() == 0)
	{
		buffer[RED] = colour;
		buffer[GREEN] = colour >> 8;
		buffer[BLUE] = colour >> 16;
		buffer[ALPHA] = alpha;
	}
	else
	{
		buffer[RED] = colour >> 16;
		buffer[GREEN] = colour >> 8;
		buffer[BLUE] = colour;
		buffer[ALPHA] = alpha;
	}
}

void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	if (x >= 0 && x < X && y >= 0 && y < Y)
		mlx_put_pixel(image, x, y, pixel_color);
}
