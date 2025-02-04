#include "../includes/minirt.h"

int failure(char *message)
{
    printf("Error: %s\n", message);
    return (FAILURE);
}
