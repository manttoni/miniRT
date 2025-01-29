#include "../libft/includes/libft.h"
#include "../includes/object.h"

static void addShapes(char **shapes)
{
    shapes[CAMERA] = "C ";
    shapes[LIGHT] = "L ";
    shapes[AMBIENT] = "A ";
    shapes[SPHERE] = "sp ";
    shapes[PLANE] = "pl ";
    shapes[CYLINDER] = "cy ";
    shapes[NONE] = NULL;
}

t_type  getType(char *line)
{
    char    *shapes[NONE + 1];
    int     i;

    addShapes(shapes);
    i = 0;
    while (shapes[i] != NULL)
    {
        if (ft_strncmp(*shapes, line, ft_strlen(*shapes)) == 0)
            return (i);
        i++;
    }
    return (NONE);
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
    t_type  type;

    type = getType(line);
    if (ft_isspace(*line) || ft_strlen(line) == 0 || type == NONE)
        return (NULL);
    
    return (line);
}