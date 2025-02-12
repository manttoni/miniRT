#include "../includes/minirt.h"



int	assign_plane(t_object *plane, char **info)
{
	plane->location = parse_vector(info[1]);
	plane->orientation = parse_vector(info[2]);
	if ((plane->orientation.x > 1.0 || plane->orientation.x < -1.0)
		|| (plane->orientation.y > 1.0 || plane->orientation.y < -1.0)
		|| (plane->orientation.z > 1.0 || plane->orientation.z < -1.0))
		return (failure("Orientation should be [1.0, -1.0]"));
	plane->color = parse_color(info[3]);
	plane->orientation = normalize_vector(plane->orientation); // for easier testing
	if (!is_normalized_vector(plane->orientation))
		return (failure("Plane orientation not normalized"));
	plane->collisionf = &plane_collision;
	return (SUCCESS);
}