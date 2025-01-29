#include "../includes/minirt.h"

static void add_shapes(char **shapes)
{
    shapes[CAMERA] = "C ";
    shapes[LIGHT] = "L ";
    shapes[AMBIENT] = "A ";
    shapes[SPHERE] = "sp ";
    shapes[PLANE] = "pl ";
    shapes[CYLINDER] = "cy ";
    shapes[NONE] = NULL;
}

t_type  get_type(char *line)
{
    char    *shapes[7];
    int     i;

    add_shapes(shapes);
    i = 0;
    while (shapes[i] != NULL)
    {
        if (ft_strncmp(shapes[i], line, ft_strlen(shapes[i])) == 0)
            return (i);
        i++;
    }
    return (NONE);
}

#include <stdio.h>
/*t_validate  *get_checks(t_type type)
{
    printf("type: %d\n", type);
    if (type == AMBIENT)
        return (AMBIENT_VALID);
    if (type == CAMERA)
        return (CAMERA_VALID);
    if (type == LIGHT)
        return (LIGHT_VALID);
    if (type == SPHERE)
        return (SPHERE_VALID);
    if (type == PLANE)
        return (PLANE_VALID);
    if (type == CYLINDER)
        return (CYLINDER_VALID);
    return (NULL);
}*/

int (**get_checks(t_type type, int (**checks)(char *)))(char *)
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
    else if (type == CYLINDER)
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_double;
        checks[3] = &is_double;
        checks[4] = &is_color;
        checks[5] = NULL;
    }
    else
        checks = NULL;
    return (checks);
}

char    *skip_spaces(char *str)
{
    if (str == NULL)
        return (NULL);
    while (ft_isspace(*str))
        str++;
    return (str);
}

static char *next_value(char *ptr)
{
    ptr = ft_strchr(ptr, ' ');
    return (skip_spaces(ptr));
}

/*
    A double[0.0,1.0] color
    C vector norm_vector int
    L vector double[0.0,1.0] color
    sp vector double color
    pl vector norm_vector color
    cy vector norm_vector double double color
*/
char    *validate(char *line)
{
    int  	(*checks[6])(char *);
    char 	*ptr;
    int  	i;
	t_type	type;

    if (line == NULL || ft_isspace(*line) || *line == '\0')
        return (NULL);

    type = get_type(line);
	if (type == NONE)
		return (NULL);
	get_checks(type, checks);
    ptr = line;
	i = 0;
    while(checks[i] != NULL)
    {
        ptr = next_value(ptr);
		if (ptr == NULL)
			return (NULL);
        if ((checks[i])(ptr) == 0)
            return (NULL);
        else
            printf("Check %d success\n", i);
        i++;
    }
    printf("Validate success\n");
    return (line);
}
