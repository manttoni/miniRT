#ifndef OBJECT_H
# define OBJECT_H

# include "./vector.h"
# include "./linked_list.h"
# include "./ray.h"

# include <stdlib.h>
# include <errno.h>

typedef enum e_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

/* type			ambient	camera	light	sphere	plane	cylinder
   color		YES		NO		NO*		YES		YES		YES
   brightness	YES		NO		YES		NO		NO		NO
   location		NO		YES		YES		YES		YES		YES
   orientation	NO		YES		NO		NO		YES		YES
   fov			NO		YES		NO		NO		NO		NO
   diameter		NO		NO		NO		YES		NO		YES
   height		NO		NO		NO		NO		NO		YES
   *) light has color in bonus
   */
typedef struct	s_object
{
	t_type		type;
	int			color;
	double		brightness;
	t_vector	location;
	t_vector	orientation;
	int			fov;
	double		diameter;
	double		height;
	int			(*collision)(t_ray *, struct s_object *);
	int			view_distance; // for camera
}	t_object;

t_object	*get_camera(t_node *objects);
int plane_collision(t_ray *ray, t_object *plane);
double		parse_double(char *str);

/* Object parsers */
t_object	*parse_object(char *line);
int			parse_orientation(char *str, t_vector *orientation);
int			parse_location(char *str, t_vector *location);
int			parse_color(char *str);

/* Collision detectors
 * 	Parameters:
 * 		-ray as a direction vector (normalized? might not matter)
 * 		-shape itself
 * 		-distance pointer
 * 	Returns: color of visible point (final color?) */

int			sphere_collision(t_ray *ray, t_object *sphere);

/* Shaped object creators */
t_object	*create_sphere(char **info);
t_object	*create_plane(char **info);
t_object	*create_cylinder(char **info);

/* Non-shaped object creators */
t_object	*create_ambient(char **info);
t_object	*create_camera(char **info);
t_object	*create_light(char **info);

#endif
