#include "../inc/minirt.h"

double	parse_brightness(char *str)
{
	int	decimals;

	if (ft_strcmp(str, "1.0") != 0 && ft_strncmp(str, "0.", 2) != 0)
		return (-1);
	if (ft_strcmp(str, "1.0") == 0)
		return (1.0);
	decimals = ft_atoi(str + 2);
	return (decimals / (ft_strlen(str + 2) * 10));
}

int	parse_color(char *str)
{
	char	**colors;
	int		ret;

	if (ft_countchar(str, ',') != 2)
		return (-1);
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (-1);
	ret = ft_atoi(colors[0]) << 16 | ft_atoi(colors[1]) << 8 | ft_atoi(colors[2]);
	free_array(colors);
	return (ret);
}

int	parse_location(char *str, t_vector *location)
{
	char		**coords;
	
	coords = ft_split(str, ',');
	if (coords == NULL)
		return (-1);
	location->x = ft_atoi(coords[0]);
	location->y = ft_atoi(coords[1]);
	location->z = ft_atoi(coords[2]);
	free_array(coords);
	return (1);
}

int	parse_orientation(char *str, t_vector *orientation)
{
	return (parse_location(str, orientation));
}

int	parse_fov(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (-1);
	return (ft_atoi(str));
}

/* Parser for doubles that are >= 0
   if invalid, return -1 */
double	parse_udouble(char *str)
{
	char	**parts;
	int		i;
	double	ret;

	if (ft_countchar(str, '.') != 1)
		return (-1);
	i = 0;
	while (ft_isdigit(str[i]) || str[i] == '.')
		i++;
	if (str[i])
		return (-1);
	parts = ft_split(str, '.');
	if (parts == NULL)
		return (-1);
	ret = ft_atoi(parts[0]) + (ft_atoi(parts[1]) / (ft_strlen(parts[1]) * 10));
	free_array(parts);
	return (ret);
}
