
#include "../includes/minirt.h"

/**
 * color_pixel - Sets the color of a specific pixel in an MLX42 image.
 * @image: Pointer to the MLX42 image where the pixel will be modified.
 * @pixel_color: The 32-bit RGBA color to set for the pixel.
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 *
 * This function calculates the correct index for the pixel in the image buffer
 * and assigns the given color value to it. The image pixels are stored as a
 * linear array, so the index is computed as `y * width + x`.
 *
 * Note: Ensure that `x` and `y` are within valid image bounds before calling.
 */

void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	int	pixel_index;

	pixel_index = y * X + x;
	((uint32_t *)(image->pixels))[pixel_index] = pixel_color;

}

/**
 * recompose_color - Converts an RGB color struct into a 32-bit RGBA integer.
 * @color: The t_color struct containing red, green, and blue values.
 *
 * This function converts an `t_color` structure (which has separate `r`, `g`, `b` values)
 * into a **single 32-bit integer** representing an **RGBA** color.
 *
 * Format: `0xAARRGGBB` (Alpha, Red, Green, Blue)
 * - The alpha channel is set to 255 (fully opaque).
 * - The red component is shifted 16 bits left.
 * - The green component is shifted 8 bits left.
 * - The blue component remains as is.
 *
 * Return: The **32-bit color** value in **RGBA format**.
 */
uint32_t    recompose_color(t_color color)
{
    return (255 << 24 | color.r << 16 | color.g << 8 | color.b);
}

/**
 * decompose_color - Extracts the RGB components from a 32-bit color value.
 * @color: The 32-bit RGBA color.
 *
 * This function extracts the **red, green, and blue components** from a **32-bit**
 * color value, storing them in a `t_color` struct.
 *
 * Extraction:
 * - Red (`r`) is obtained by shifting right **16 bits** and masking the last 8 bits.
 * - Green (`g`) is obtained by shifting right **8 bits** and masking the last 8 bits.
 * - Blue (`b`) is obtained by masking the last 8 bits.
 * - Alpha is ignored (not used in the struct).
 *
 * Return: A `t_color` struct containing the **RGB** components.
 */
t_color     decompose_color(uint32_t color)
{
    t_color decomposed;

    decomposed.r = color >> 16 & 0xFF;
    decomposed.g = color >> 8 & 0xFF;
    decomposed.b = color & 0xFF;
    return (decomposed);
}

/**
 * color_intensity - Modifies the brightness of a 32-bit color.
 * @color: The original 32-bit RGBA color.
 * @intensity: A multiplier for brightness (range: 0.0 to 1.0).
 *
 * This function adjusts the intensity of a color by multiplying the **RGB**
 * components by the given `intensity` factor.
 *
 * Behavior:
 * - If `intensity = 1.0`, the color remains unchanged.
 * - If `intensity < 1.0`, the color is **darkened**.
 * - If `intensity > 1.0`, the color is **brightened** (may require clamping).
 * - If `intensity = 0.0`, the color becomes **black**.
 *
 * Return: The modified 32-bit RGBA color.
 */
uint32_t    color_intensity(uint32_t color, double intensity)
{
    t_color decomposed;

    decomposed = decompose_color(color);
    decomposed.r *= intensity;
    decomposed.g *= intensity;
    decomposed.b *= intensity;
    return (recompose_color(decomposed));
}
