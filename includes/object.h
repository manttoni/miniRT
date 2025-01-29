#ifndef OBJECT_H
# define OBJECT_H

# include "./vector.h"
# include "./linked_list.h"
# include "./ray.h"

# include <stdlib.h>
# include <errno.h>

typedef enum e_type
{
	CAMERA,
	LIGHT,
	AMBIENT,
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}	t_type;

typedef struct s_camera_info
{
	unsigned int	view_distance;
	t_vector		u;
	t_vector		v;
	t_ray			ray;
}	t_camera_info;

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
	t_type			type;
	uint32_t		color;
	double			brightness;
	t_vector		location;
	t_vector		orientation;
	int				fov;
	double			diameter;
	double			height;
	int				(*collision)(t_ray *, struct s_object *);
	t_camera_info	info;
}	t_object;

void			print_object(t_object *o);
t_object		*get_object(t_node *objects, t_type type);
t_camera_info 	image_plane(t_object *camera);
int 			plane_collision(t_ray *ray, t_object *plane);
double			parse_double(char *str);

/* Object parsers */
t_object	*parse_object(char *line);
int			parse_orientation(char *str, t_vector *orientation);
int			parse_location(char *str, t_vector *location);
int			parse_color(char *str);

/* Shaped object creators */
t_object	*create_sphere(char **info);
t_object	*create_plane(char **info);
t_object	*create_cylinder(char **info);

/* Non-shaped object creators */
t_object	*create_ambient(char **info);
t_object	*create_camera(char **info);
t_object	*create_light(char **info);

#endif
