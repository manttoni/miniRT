
#include "../includes/minirt.h"

void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	if (x >= 0 && x < X && y >= 0 && y < Y)
		mlx_put_pixel(image, x, y, pixel_color);
}

uint32_t    recompose_color(t_color color)
{
    return (255 << color.r | color.g << 16 | color.b << 8 | 255);
}

t_color     decompose_color(uint32_t color)
{
    t_color decomposed;

	decomposed.r = color >> 24 & 0xFF;
    decomposed.g = color >> 16 & 0xFF;
    decomposed.b = color >> 8 & 0xFF;
    decomposed.a = color & 0xFF;
    return (decomposed);
}

static t_color	average_colors(t_color a, t_color b, t_color c, t_color d)
{
	t_color	avg;

	avg.r = (a.r + b.r + c.r + d.r) / 4;
	avg.g = (a.g + b.g + c.g + d.g) / 4;
	avg.b = (a.b + b.b + c.b + d.b) / 4;
	avg.a = 255;
	return (avg);
}

t_color	get_pixel_color(mlx_image_t *image, int x, int y)
{
	t_color	color;
	int		index;

	ft_memset(&color, 0, sizeof(t_color));
	if (x < 0 || x >= X || y < 0 || y >= Y)
		return (color);
	index = (y * X + x) * 4;
	color.r = image->pixels[index];
	color.g = image->pixels[index + 1];
	color.b = image->pixels[index + 2];
	color.a = 255;
	return (color);
}

void interpolate_missing_pixels(t_data *data)
{
	int x, y;
	t_color c1, c2, c3, c4;

	for (y = 0; y < Y; y++)
	{
		for (x = 0; x < X; x++)
		{
			// If the pixel was already raycasted, skip it
			if ((x % 2 == 0) && (y % 2 == 0))
				continue;

			// Get surrounding colors (handling edge cases)
			c1 = get_pixel_color(data->image, x - (x % 2), y - (y % 2)); // Top-left
			c2 = get_pixel_color(data->image, x + (2 - (x % 2)), y - (y % 2)); // Top-right
			c3 = get_pixel_color(data->image, x - (x % 2), y + (2 - (y % 2))); // Bottom-left
			c4 = get_pixel_color(data->image, x + (2 - (x % 2)), y + (2 - (y % 2))); // Bottom-right

			// Bilinear interpolation
			t_color interpolated_color = average_colors(c1, c2, c3, c4);
			color_pixel(data->image, recompose_color(interpolated_color), x, y);
		}
	}
}
