#include "../includes/minirt.h"

static size_t	fract_len(char *ptr)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(ptr[len]))
		len++;
	return (len);
}

/* Parses a double until a non double character is found
	assumes the format has been validated */
double	parse_double(char *str)
{
	int		int_part;
	int		fract_part;
	int		sign;
	char	*dot;
	char	*comma;

	sign = 1;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	int_part = 0;
	dot = ft_strchr(str, '.');
	comma = ft_strchr(str, ',');
	if (*str != '.')
		int_part = ft_atoi(str);
	if (dot == NULL || (comma != NULL && comma < dot))
		return (sign * (double)int_part);
	fract_part = ft_atoi(dot + 1);
	return ((sign * int_part)
		+ (sign * fract_part / pow(10, fract_len(dot + 1))));
}

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
