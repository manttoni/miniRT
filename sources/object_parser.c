#include "../includes/minirt.h"

t_vector	parse_vector(char *str)
{
	t_vector	v;

	v.x = parse_double(str);
	str = ft_strchr(str, ',') + 1;
	v.y = parse_double(str);
	str = ft_strrchr(str, ',') + 1;
	v.z = parse_double(str);
	return (v);
}

uint32_t	parse_color(char *str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str);
	g = ft_atoi(ft_strchr(str, ',') + 1);
	b = ft_atoi(ft_strrchr(str, ',') + 1);
	return (r << 24 | g << 16 | b << 8 | 255);
}
