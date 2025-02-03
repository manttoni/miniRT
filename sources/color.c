
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
	// int	pixel_index;

	// pixel_index = y * X + x;
	// ((uint32_t *)(image->pixels))[pixel_index] = pixel_color;
	// int	dot;
	// int	alpha;

	// alpha = 0xFF;
	// if (x > X || y > Y || x < 0 || y < 0)
	// 	return ;
	// dot = ((int)round(y) * X * 4) + ((int)round(x) * 4);
	// base_pixel(&image->pixels[dot], pixel_color, alpha);

	if (x >= 0 && x < X && y >= 0 && y < Y)
		mlx_put_pixel(image, x, y, pixel_color);
}
