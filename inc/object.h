#ifndef OBJECT_H
# define OBJECT_H

# include "../inc/vector.h"

typedef struct	s_sphere
{
	t_vector	center;
	double		diameter;
	int			color;
}	t_sphere;

/*				ambient	camera	light	sphere	plane	cylinder
   type			YES		YES		YES		YES		YES		YES
   color		YES		NO		NO		YES		YES		YES
   brightness	YES		NO		YES		NO		NO		NO
   location		NO		YES		YES		YES		YES		YES
   orientation	NO		YES		NO		NO		YES		YES
   fov			NO		YES		NO		NO		NO		NO
   diameter		NO		NO		NO		YES		NO		YES
   height		NO		NO		NO		NO		NO		YES
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
}	t_object;

typedef enum e_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER;
}	t_type;

t_object	*parse_object(char *line);
t_sphere	*create_sphere(t_vector center, double diameter, int color);
int			sphere_collision(t_vector d, t_sphere *sphere, double *distance);

#endif
