#include "../includes/minirt.h"
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return 2;

	//char *str = validate(av[1]);
	//if (str == NULL)
	//	return 1;
	
	t_object *o = parse_object(av[1]);
	if (o == NULL)
		return (1);
	return 0;
}
