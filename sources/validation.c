#include "../includes/minirt.h"

static void    assign_checks(t_type type, int (**checks)(char *))
{
    if (type == AMBIENT)
    {
        checks[0] = &is_double;
        checks[1] = &is_color;
        checks[2] = NULL;
    }
    else if (type == CAMERA)
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_int;
        checks[3] = NULL;
    }
    else if (type == LIGHT)
    {
        checks[0] = &is_vector;
        checks[1] = &is_double;
        checks[2] = NULL;
    }
    else if (type == SPHERE)
    {
        checks[0] = &is_vector;
        checks[1] = &is_double;
        checks[2] = &is_color;
        checks[3] = NULL;
    }
    else if (type == PLANE)
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_color;
        checks[3] = NULL;
    }
    else
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_double;
        checks[3] = &is_double;
        checks[4] = &is_color;
        checks[5] = NULL;
    }
}

static char *next_value(char *ptr)
{
    ptr = ft_strchr(ptr, ' ');
    if (ptr == NULL)
        return (NULL);
    while (ft_isspace(*ptr))
        ptr++;
    return (ptr);
}

char    *validate(char *line)
{
    int  	(*checks[6])(char *);
    char 	*ptr;
    int  	i;
	t_type	type;

    type = get_type(line);
    if (line == NULL || ft_isspace(*line) || *line == '\0' || type == NONE)
        return (NULL);
    assign_checks(type, checks);
    ptr = line;
	i = 0;

    while(checks[i] != NULL)
    {
        ptr = next_value(ptr);
		if (ptr == NULL || (checks[i])(ptr) == 0)
        {
            if (type == PLANE)
                printf("Failed at check: %d\n", i);
            return (NULL);
        }
        i++;
    }
    //printf("Validation success: %s\n", line);
    return (line);
}
