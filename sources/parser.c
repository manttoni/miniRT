#include "../libft/includes/libft.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>

size_t	doublelen(char *str)
{
	size_t	len;
	int	periods;
	int	minus;

	len = 0;
	periods = 0;
	minus = 0;
	while (ft_isdigit(str[len])
		|| (str[len] == '.' && periods <= 1)
		|| (str[len] == '-' && minus <= 1))
	{
		if (str[len] == '.')
			periods++;
		if (str[len] == '-')
		{
			if (periods == 1)
				return (0);
			minus++;
		}
		len++;
	}
	if (len == 1 && (str[0] == '.' || str[0] == '-'))
		return (0);
	return (len);
}

int	valid_double(char *str)
{
	if (ft_strlen(str) != doublelen(str))
	{
		errno = EINVAL;
		return (0);
	}
	return (1);
}

double	parse_double(char *str)
{
	char	*period;
	double	int_part;
	double	fract_part;
	int		sign;

	if (valid_double(str) == 0)
	{
		printf("%s is not a valid double\n", str);
		return (0);
	}
	sign = 1;
	if (*str == '-')
		sign = -1;
	int_part = (double) ft_atoi(str);
	period = ft_strchr(str, '.');
	if (period == NULL)
		return (int_part);
	fract_part = (double) ft_atoi(period + 1);
	return (int_part + sign * fract_part / pow(10, ft_strlen(period + 1)));
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
