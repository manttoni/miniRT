#include "../includes/minirt.h"
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return 2;

	t_object o;
	return parse_object(&o, av[1]);
}
