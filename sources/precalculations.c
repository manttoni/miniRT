#include "../includes/minirt.h"

/* Calculates the distance to the image plane from the camera so that the angle is fov */
double	calc_view_distance(int fov)
{
	double	fov_rad;

	fov_rad = fov * M_PI / 180;
	return ((X / 2) / tan(fov_rad / 2));
}
t_image_plane image_plane(t_object *camera)
{
	t_image_plane info;

	info.view_distance = calc_view_distance(camera->fov);

	// Choose an initial "up" vector that avoids gimbal lock
	t_vector up = vector(0, 1, 0);
	if (fabs(camera->orientation.y) > 0.99) // Avoiding near-vertical issues
		up = vector(1, 0, 0);

	// Right vector (u) is perpendicular to both up and camera orientation
	info.u = normalize_vector(cross_product(up, camera->orientation));

	// Up vector (v) is perpendicular to both orientation and right vector
	info.v = normalize_vector(cross_product(camera->orientation, info.u));

	// Ensure v is always consistently oriented to avoid flipping
	if (dot(info.v, up) < 0)
		info.v = v_mul(-1, info.v);

	// Set ray properties
	info.ray.start = camera->location;
	info.ray.end = camera->location;
	info.ray.direction = v_mul(info.view_distance, camera->orientation);
	info.ray.direction = v_sum(camera->location, info.ray.direction);
	info.ray.color = BACKGROUND_COLOR;
	info.ray.distance = DBL_MAX;
	info.ray.object = NULL;

	return info;
}

/* Precalculates numerator which is used in plane_collision */
void	precalculate_plane(t_object *plane, t_image_plane info)
{
	double	d;

	d = dot(plane->orientation, plane->location);
	info.ray.start = v_sum(info.ray.start, vector(0.0001, 0.0001, 0.0001));
	plane->numerator = -dot(plane->orientation, info.ray.start) + d;
}


/* Calculates all precalculations
    image_plane for u,v,view_distance, base ray*/
void	set_precalculations(t_data  *data)
{
	data->info = image_plane(data->camera);
}

/* precalculations for image plane basic vectors
	ray gets values that are initially always the same */
// t_image_plane	image_plane(t_object *camera)
// {
// 	t_image_plane	info;

// 	info.view_distance = calc_view_distance(camera->fov);
// 	if (camera->orientation.x == 0 && camera->orientation.y == 0)
// 		info.u = vector(1, 0, 0);
// 	else if (camera->orientation.y == 0 && camera->orientation.z == 0)
// 		info.u = vector (0, 1, 0);
// 	else if (camera->orientation.z == 0 && camera->orientation.x == 0)
// 		info.u = vector (0, 0, 1);
// 	else
// 		info.u = vector(-camera->orientation.y, camera->orientation.x, 0);
// 	info.u = normalize_vector(info.u);
// 	info.v = normalize_vector(cross_product(camera->orientation, info.u));
// 	// info.v = cross_product(camera->orientation, info.u);
// 	info.ray.start = camera->location;
// 	info.ray.end = camera->location;
// 	info.ray.direction = v_mul(info.view_distance, camera->orientation);
// 	info.ray.direction = v_sum(camera->location, info.ray.direction);
// 	info.ray.color = BACKGROUND_COLOR;
// 	info.ray.distance = DBL_MAX;
// 	info.ray.object = NULL;
// 	return (info);
// }
