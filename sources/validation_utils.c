#include "../libft/includes/libft.h"

/*
    delimit is f.e. ' ' or ','
*/
int is_double(char *ptr, char delimit)
{
    int periods;
    int digits;

    periods = 0;
    digits = 0;
    while (!ft_isspace(*ptr) && *ptr != delimit && *ptr != '\0')
    {
        if (ft_isdigit(*ptr))
            digits++;
        else if (*ptr == '.')
            periods++;
        else
            return (0);
        ptr++;
    }
    return (periods <= 1 && digits >= 1);
}

int is_color(char *ptr)
{
    int commas;
    int values;

    commas = 0;
    values = 0;
    while (!ft_isspace(*ptr) && *ptr != '\0')
    {
        if (is_digit(*ptr) || ft_atoi(*ptr) / 256 == 0)
            values++;
        while (ft_isdigit(*ptr))
            ptr++;
        if (*ptr != ',')
            break;
        commas++;
        ptr++;
    }
    return (values == 3 && commas == 2);
}

int is_vector(char *ptr)
{
    int commas;
    int doubles;

    commas = 0;
    doubles = 0;
    while (!ft_isspace(*ptr) && *ptr != '.')
    {
        if (is_double(*ptr, ','))
            doubles++;
        while (ft_isdigit(*ptr) || *ptr == '.')
            ptr++;
        if (*ptr != ',')
            break;
        commas++;
        ptr++;
    }
    return (doubles == 3 && commas == 2);
}

int is_int(char *ptr)
{
    while (!ft_isspace(*ptr) && *ptr != '\0')
    {
        if (!ft_isdigit(*ptr))
            return (0);
        ptr++;
    }
    return (1);
}

