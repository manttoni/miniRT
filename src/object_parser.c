#include "../inc/minirt.h"

int	parse_location(char *str, t_vector *location)
{
	char	**coords;

	coords = ft_split(str, ',');
	if (coords == NULL)
		return (-1);
	location->x = parse_double(coords[0]);
	location->y = parse_double(coords[1]);
	location->z = parse_double(coords[2]);
	free_array(coords);
	if (errno == EINVAL)
		return (-1);
	return (1);
}

int parse_orientation(char *str, t_vector *orientation)
{
	int	location;

	location = parse_location(str, orientation);
	if (location < 0)
		return (location);
	if (vector_len(*orientation) != 1)
		return (-1);
	return (1);
}

int	parse_color(char *str)
{
	int	r;
	int	g;
	int	b;

	if (ft_countchar(str, ',') != 2)
	{
		errno = EINVAL;
		return (-1);
	}
	r = ft_atoi(str);
	g = ft_atoi(ft_strchr(str, ',') + 1);
	b = ft_atoi(ft_strrchr(str, ',') + 1);
	if (min(r, min(g, b)) < 0)
	{
		errno = EINVAL;
		return (-1);
	}
	return (r << 16 | g << 8 | b);
}
