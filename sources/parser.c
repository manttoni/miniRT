#include "../includes/minirt.h"

/**
 * doublelen - Determines the valid length of a floating-point number in a string.
 * @str: The input string containing a potential floating-point number.
 *
 * This function:
 * - Iterates through `str` and counts valid characters (digits, `.` for decimals, and `-` for negative).
 * - Ensures:
 *   - Only one `.` (decimal point) is allowed.
 *   - Only one `-` (negative sign) is allowed and must be at the **beginning**.
 *   - If `.` is the first character or `-` follows `.`, it returns `0` (invalid).
 *
 * Return:
 * - The length of a valid double in `str`.
 * - `0` if the format is invalid.
 */
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

/**
 * valid_double - Checks if a string represents a valid floating-point number.
 * @str: The input string.
 *
 * This function:
 * - Calls `doublelen(str)` to determine how much of `str` is a valid floating-point number.
 * - If `ft_strlen(str) != doublelen(str)`, it means `str` contains **extra invalid characters**.
 * - If invalid, sets `errno = EINVAL` (error handling).
 *
 * Return:
 * - `1` if `str` is a valid floating-point number.
 * - `0` if `str` contains **invalid characters** or incorrect format.
 */
int	valid_double(char *str)
{
	if (ft_strlen(str) != doublelen(str))
	{
		errno = EINVAL;
		return (0);
	}
	return (1);
}

/**
 * parse_double - Converts a valid string representation of a double to `double`.
 * @str: The input string (must be validated before calling).
 *
 * This function:
 * - Calls `valid_double(str)`. If invalid, prints an error and returns `0.0`.
 * - Handles **integer part** and **fractional part** separately.
 * - Extracts the **sign** (`-` or `+`).
 * - Finds the `.` decimal point using `ft_strchr()`.
 * - Uses `pow(10, len)` to divide the fractional part correctly.
 * - Returns the computed `double` value.
 *
 * Return:
 * - The **double** representation of `str`.
 * - `0.0` if `str` is invalid.
 */
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
