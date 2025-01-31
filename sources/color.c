
#include "../includes/minirt.h"

void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	int	pixel_index;

	pixel_index = y * X + x;
	((uint32_t *)(image->pixels))[pixel_index] = pixel_color;

}

uint32_t    recompose_color(t_color color)
{
    return (255 << 24 | color.b << 16 | color.g << 8 | color.r);
}

t_color     decompose_color(uint32_t color)
{
    t_color decomposed;

    decomposed.b = (color >> 16) & 0xFF;
    decomposed.g = (color >> 8) & 0xFF;
    decomposed.r = (color) & 0xFF;
    return (decomposed);
}

uint32_t    color_intensity(uint32_t color, double intensity)
{
    t_color decomposed;

    decomposed = decompose_color(color);
    decomposed.r *= intensity;
    decomposed.g *= intensity;
    decomposed.b *= intensity;
    return (recompose_color(decomposed));
}

uint32_t mix_colors(uint32_t o_color, uint32_t l_color)
{
    int r;
    int g;
    int b;

    b = ((o_color >> 16 ) & 0xFF) * ((l_color >> 16 ) & 0xFF) / 255;
    g = ((o_color >> 8 ) & 0xFF) * ((l_color >> 8 ) & 0xFF) / 255;
    r = (o_color & 0xFF) * (l_color & 0xFF) / 255;
    return (255 << 24 | b << 16 | g << 8 | r);
}
