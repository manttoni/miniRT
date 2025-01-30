#include "../includes/minirt.h"

size_t	fract_len(char *ptr)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(ptr[len]))
		len++;
	return (len);
}

double	parse_double(char *str)
{
	int		int_part;
	int		fract_part;
	int		sign;
	char	*dot;

	sign = 1;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	int_part = 0;
	dot = ft_strchr(str, '.');
	if (*str != '.')
		int_part = ft_atoi(str);
	if (dot == NULL)
		return (sign * (double)int_part);
	fract_part = ft_atoi(dot + 1);
	return ((sign * int_part) + (sign * fract_part / pow(10, fract_len(dot + 1))));
}
/*
#include <stdio.h>

int main(void)
{
	double a = parse_double("1.1");
	double b = parse_double(".1");
	double c = parse_double("1.");
	double d = parse_double("-1.1");
	double e = parse_double("-.1");
	double f = parse_double("1");
	printf("%f %f %f %f %f %f\n", a, b, c, d, e, f);
	printf("%d\n", errno);
	double g = parse_double("-");
	printf("%d\n", errno);
}*/
