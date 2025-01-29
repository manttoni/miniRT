#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
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
	struct s_object *next;
}	t_object;

t_object	*last_object(t_object *list);
int			add_node(t_object **list, t_object *new);
void		free_list(t_object *list);
t_object	*create_node(char *line);
double  closest(t_ray *ray, t_object *objects);

void			print_object(t_object *o);
t_object		*get_object(t_object *objects, t_type type);
t_camera_info 	image_plane(t_object *camera);
// int 			plane_collision(t_ray *ray, t_object *plane);
double			parse_double(char *str);

/* Object parsers */
void		parse_object(t_object	*object, char *line);
int			parse_orientation(char *str, t_vector *orientation);
int			parse_location(char *str, t_vector *location);
int			parse_color(char *str);

/* Shaped object creators */
void	create_sphere(t_object *object, char **info);
void	create_plane(t_object *object, char **info);
void	create_cylinder(t_object *object, char **info);

/* Non-shaped object creators */
void	create_ambient(t_object *object, char **info);
void	create_camera(t_object *object, char **info);
void	create_light(t_object *object, char **info);

#endif
