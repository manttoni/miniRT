#include "../includes/minirt.h"

/**
 * parse_location - Parses a string containing 3D coordinates into a vector.
 * @str: The input string (format: "x,y,z").
 * @location: Pointer to a `t_vector` struct to store the parsed coordinates.
 *
 * This function:
 * - Splits the string using `,` as a delimiter.
 * - Converts each component (`x, y, z`) from string to `double`.
 * - Frees the allocated array after parsing.
 * - Checks for parsing errors using `errno`.
 *
 * Return:
 * - `1` on success.
 * - `-1` if parsing fails.
 */
int	parse_location(char *str, t_vector *location)
{
	char	**coords;

	coords = ft_split(str, ',');
	if (coords == NULL)
		return (-1);
	location->x = parse_double(coords[0]);
	location->y = parse_double(coords[1]);
	location->z = parse_double(coords[2]);
	ft_free_array(coords);
	if (errno == EINVAL)
		return (-1);
	return (1);
}

/**
 * parse_orientation - Parses and normalizes a vector for orientation.
 * @str: The input string (format: "x,y,z").
 * @orientation: Pointer to a `t_vector` struct to store the parsed values.
 *
 * This function:
 * - Calls `parse_location(str, orientation)` to extract the vector.
 * - Normalizes the vector to ensure its length is exactly **1.0**.
 * - Prints a warning if the vector is not normalized.
 *
 * Return:
 * - `1` on success.
 * - `-1` if parsing fails or if the vector is not normalized.
 */
int parse_orientation(char *str, t_vector *orientation)
{
	int	location;

	location = parse_location(str, orientation);
	if (location < 0)
		return (location);
	// normalize vector for easier testing
	*orientation = normalize_vector(*orientation);
	if (v_len(*orientation) > 1 + EPSILON || v_len(*orientation) < 1 - EPSILON)
	{
		printf("Orientation vector not normalized\n");
		return (-1);
	}
	return (1);
}

/**
 * parse_color - Converts a string containing RGB values into a 32-bit color.
 * @str: The input string (format: "R,G,B").
 *
 * This function:
 * - Ensures the input contains exactly **two commas** (valid format check).
 * - Extracts the **red, green, and blue components**.
 * - Sets the **alpha (opacity) component to 255**.
 * - Returns a **32-bit color in ARGB format** (`0xAARRGGBB`).
 * - If any value is negative, sets `errno = EINVAL` and returns `-1`.
 *
 * Return:
 * - A **32-bit integer** representing the color (`0xAARRGGBB`).
 * - `-1` if parsing fails.
 */
int	parse_color(char *str)
{
	int	r;
	int	g;
	int	b;
	int a;

	if (ft_countchar(str, ',') != 2)
	{
		errno = EINVAL;
		return (-1);
	}
	r = ft_atoi(str);
	g = ft_atoi(ft_strchr(str, ',') + 1);
	b = ft_atoi(ft_strrchr(str, ',') + 1);
	a = 255;
	if (min(r, min(g, b)) < 0)
	{
		errno = EINVAL;
		return (-1);
	}
	return (a << 24 | r << 16 | g << 8 | b);
}
