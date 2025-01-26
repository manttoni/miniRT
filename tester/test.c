#include <stdio.h>
#include "../includes/object.h"
#include <math.h>

int main(int ac, char **av)
{
	t_object *object = parse_object(av[1]);

	if (ac != 2)
		return 2;

	if (object == NULL)
		return 1;

	free(object);
	return 0;
}
