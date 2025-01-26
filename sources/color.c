#include "../includes/minirt.h"
#include "../includes/color.h"

uint32_t    recompose_color(t_color color)
{
    return (255 << 24 | color.r << 16 | color.g << 8 | color.b);
}

t_color     decompose_color(uint32_t color)
{
    t_color decomposed;

    decomposed.r = color >> 16 & 0xFF;
    decomposed.g = color >> 8 & 0xFF;
    decomposed.b = color & 0xFF;
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