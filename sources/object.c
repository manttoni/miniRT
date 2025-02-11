#include "../includes/minirt.h"
#include <math.h>
/*
void print_object(t_object o)
{
	if (o.type >= NONE)
	{
		printf("Unknown object\n");
		return ;
	}
	printf("---------------\n");
	if (o.type == CAMERA)
		printf("Camera: 📷\n");
	else if (o.type == SPHERE)
		printf("Sphere: ⚪\n");
	else if (o.type == PLANE)
		printf("Plane: ✈️\n");
	else if (o.type == AMBIENT)
		printf("Ambient light: 🌓\n");
	else if (o.type == LIGHT)
		printf("Light: 💡\n");
	else if (o.type == CYLINDER)
		printf("Cylinder: 🛢\n");
	if (o.type != AMBIENT)
	{
		printf("Location: ");
		print_vector(o.location);
	}
	if (o.type == CAMERA || o.type == PLANE || o.type == CYLINDER)
	{
		printf("Orientation: ");
		print_vector(o.orientation);
	}
	if (o.type == CAMERA)
		printf("FOV: %d\nView distance: %1.2f\n", o.fov, o.info.view_distance);
	if (o.type == SPHERE || o.type == CYLINDER)
		printf("Diameter: %f\n", o.diameter);
	if (o.type != CAMERA && o.type != LIGHT)
	{
		printf("Color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			   (o.color >> 24) & 0xFF, (o.color >> 16) & 0xFF,
			   (o.color >> 8) & 0xFF, o.color);
	}
	if (o.type == LIGHT || o.type == AMBIENT)
		printf("Brightness: %f\n", o.brightness);
}
*/
void print_objects(t_objarr *objarr)
{
	size_t	i;

	i = 0;
	while (i < objarr->objects)
	{
		print_object(objarr->arr[i]);
		printf("Index: %zu\n", i);
		i++;
	}
	printf("---------------\n");
}

t_type	get_type(char *line)
{
	char *shapes[7];
	int i;
	shapes[CAMERA] = "C ";
	shapes[LIGHT] = "L ";
	shapes[AMBIENT] = "A ";
	shapes[SPHERE] = "sp ";
	shapes[PLANE] = "pl ";
	shapes[CYLINDER] = "cy ";
	shapes[NONE] = NULL;
	i = 0;
	while (shapes[i] != NULL)
	{
		if (ft_strncmp(shapes[i], line, ft_strlen(shapes[i])) == 0)
		{
			return (i);
		}
		i++;
	}
	return (NONE);
}

/* Calculates the distance to the image plane from the camera so that the angle is fov */
double	calc_view_distance(int fov)
{
	double	fov_rad;

	fov_rad = fov * M_PI / 180;
	return ((X / 2) / tan(fov_rad / 2));
}

int	assign_ambient(t_object *ambient, char **info)
{
	ambient->brightness = parse_double(info[1]);
	ambient->color = parse_color(info[2]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (failure("Brightness should be [0.0, 1.0]"));
	return (SUCCESS);
}

/* precalculations for image plane basic vectors
	ray gets values that are initially always the same */
t_camera_info	image_plane(t_camera *camera)
{
	t_camera_info	info;

	info.view_distance = calc_view_distance(camera->fov);
	if (camera->orientation.x == 0 && camera->orientation.y == 0)
		info.u = vector(1, 0, 0);
	else if (camera->orientation.y == 0 && camera->orientation.z == 0)
		info.u = vector (0, 1, 0);
	else if (camera->orientation.z == 0 && camera->orientation.x == 0)
		info.u = vector (0, 0, 1);
	else
		info.u = vector(-camera->orientation.y, camera->orientation.x, 0);
	info.v = cross_product(camera->orientation, info.u);
	info.ray.start = camera->location;
	info.ray.end = camera->location;
	info.ray.direction = v_mul(info.view_distance, camera->orientation);
	info.ray.direction = v_sum(camera->location, info.ray.direction);
	info.ray.color = BACKGROUND_COLOR;
	info.ray.distance = DBL_MAX;
	info.ray.object = NULL;
	return (info);
}

int assign_camera(t_camera *camera, char *line)
{
	char	**info;

	info = ft_split(line, ' ');
	if (info == NULL)
		return (FAILURE);
	camera->location = parse_vector(info[1]);
	camera->orientation = parse_vector(info[2]);
	camera->fov = ft_atoi(info[3]);
	camera->orientation = normalize_vector(camera->orientation);
	ft_free_array(info);
	if (camera->fov < 0 || camera->fov > 180)
		return (failure("FOV not valid"));
	return (SUCCESS);
}

static int	assign_light(t_object *light, char **info)
{
	light->location = parse_vector(info[1]);
	light->brightness = parse_double(info[2]);
	if (light->brightness > 1.0 || light->brightness < 0.0)
		return (failure("Brightness should be [0.0, 1.0]"));
	return (SUCCESS);
}

static int	assign_sphere(t_object *sphere, char **info)
{
	sphere->location = parse_vector(info[1]);
	if (info[2][0] == '-')
		return (FAILURE);
	sphere->diameter = parse_double(info[2]);
	sphere->color = parse_color(info[3]);
	sphere->collisionf = &sphere_collision;
	return (SUCCESS);
}

/* Precalculates numerator which is used in plane_collision */
void	precalculate_plane(t_object *plane, t_object *camera)
{
	double	d;

	d = dot_product(plane->orientation, plane->location);
	plane->numerator = -dot_product(plane->orientation, camera->location) + d;
}

static int	assign_plane(t_object *plane, char **info)
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

static int	assign_cylinder(t_object *cylinder, char **info)
{
	cylinder->location = parse_vector(info[1]);
	cylinder->orientation = parse_vector(info[2]);
	if (info[3][0] == '-')
		return (FAILURE);
	cylinder->diameter = parse_double(info[3]);
	cylinder->height = parse_double(info[4]);
	cylinder->color = parse_color(info[5]);
	cylinder->orientation = normalize_vector(cylinder->orientation);
	// if (!is_normalized_vector(cylinder->orientation))
	// 	return (failure("Cylinder orientation not normalized"));
	cylinder->collisionf = &cylinder_collision;
	return (SUCCESS);
}

static int	assign_values(t_object *object, char **info)
{
	if (object == NULL || info == NULL)
		return (FAILURE);
	if (object->type == AMBIENT)
		return (assign_ambient(object, info));
	else if (object->type == LIGHT)
		return (assign_light(object, info));
	else if (object->type == SPHERE)
		return (assign_sphere(object, info));
	else if (object->type == PLANE)
		return (assign_plane(object, info));
	else if (object->type == CYLINDER)
		return (assign_cylinder(object, info));
	return (FAILURE);
}

int	parse_object(t_object *object, char *line)
{
	char		**info;

	object->type = get_type(line);
	info = ft_split(line, ' ');
	if (assign_values(object, info) == FAILURE)
	{
		ft_free_array(info);
		failure("assign_values FAILURE");
		return (FAILURE);
	}
	ft_free_array(info);
	return (SUCCESS);
}
