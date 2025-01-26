#include "../includes/object.h"
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return 2;

	t_object *object = parse_object(av[1]);

	if (object == NULL)
		return 1;

	free(object);
	return 0;
}
