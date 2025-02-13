#include "../includes/minirt.h"

static void assign_checks(t_type type, int (**checks)(char *))
{
	if (type == AMBIENT)
		ambient_checks(checks);
	else if (type == CAMERA)
		camera_checks(checks);
	else if (type == LIGHT)
		lights_checks(checks);
	else if (type == SPHERE)
		sphere_checks(checks);
	else if (type == PLANE)
	{
		checks[0] = &is_vector;
		checks[1] = &is_vector;
		checks[2] = &is_color;
		checks[3] = NULL;
	}
	else if (type == CYLINDER)
	{
		checks[0] = &is_vector;
		checks[1] = &is_vector;
		checks[2] = &is_double;
		checks[3] = &is_double;
		checks[4] = &is_color;
		checks[5] = NULL;
	}
}

/* Jumps to the next 'token' of the line read from the line
	first to end of 'token' and then skips all spaces
	returns NULL if there are no more 'tokens' */
static char *next_value(char *ptr)
{
	ptr = ft_strchr(ptr, ' ');
	if (ptr == NULL)
		return (NULL);
	while (ft_isspace(*ptr))
		ptr++;
	return (ptr);
}

/* Checks validity of line read from file by looping through validation functions
	every value must be correct, and there must not be any extra values */
char *validate(char *line)
{
	int (*checks[6])(char *);
	char *ptr;
	int i;
	t_type	type;

	type = get_type(line);
	if (line == NULL || ft_isspace(*line) || *line == '\0' || type == NONE)
		return (NULL);
	assign_checks(type, checks);
	ptr = line;
	i = 0;
	while (checks[i] != NULL)
	{
		ptr = next_value(ptr);
		if (ptr == NULL || (checks[i])(ptr) == 0)
		{
			printf("%s: Failed at check: %d\n", line, i);
			return (NULL);
		}
		i++;
	}
	ptr = next_value(ptr);
	if (ptr != NULL && *ptr != '\0')
	{
		printf("Wrong format(%c): %s\n", *ptr, line);
		return (NULL);
	}
	return (line);
}
