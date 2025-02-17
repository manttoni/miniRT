#ifndef MINIRT_H
# define MINIRT_H

/* Defines */
# define EPSILON 0.001
# define BACKGROUND_COLOR 0x000000ff
# define X 1000
# define Y 1000
# define FAILURE 1
# define SUCCESS 0
# define HIT 1
# define NO_HIT 0
# define TOP_CYLINDER_CAP 1
# define BOTTOM_CYLINDER_CAP 0

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <float.h>
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>

/* Enums */
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

typedef enum e_rgba
{
	RED,
	GREEN,
	BLUE,
	ALPHA
}	t_rgba;

/* Structs */
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
	t_vector		direction;
	t_vector		coll_norm;
	t_vector		end;
	t_vector		start;
	double			distance;
	uint32_t		color;
	struct s_object	*object;
}	t_ray;

typedef struct s_image_plane
{
	double		view_distance;
	t_vector	u;
	t_vector	v;
	t_ray		ray;
}	t_image_plane;

typedef struct s_object
{
	t_type		type;
	uint32_t	color;
	double		diameter;
	double		height;
	double		brightness;
	t_vector	location;
	t_vector	orientation;
	int			(*collisionf)(t_ray *, struct s_object *);
	int			fov;
}	t_object;

typedef struct s_ambient
{
	t_object	*ambient;
	t_vector	ambient_col;
}	t_ambient;

typedef struct s_light
{
	t_object	*light;
	t_vector	light_dir;
	t_vector	view_dir;
	double		diffuse;
	double		specular;
	double		shine;
	uint32_t	color;
	int			r;
	int			g;
	int			b;
}	t_light;

typedef struct s_objarr
{
	t_object	*arr;
	size_t		capacity;
	size_t		objects;
}	t_objarr;

typedef struct s_mouse
{
	int32_t	x;
	int32_t	y;
	int		left;
	int		right;
}	t_mouse;

typedef struct s_data
{
	t_objarr		*objects;
	t_object		*camera;
	t_light			*light;
	t_ambient		*ambient;
	t_image_plane	info;
	t_object		*selected;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_mouse			mouse;
	char			*file;
}	t_data;

typedef struct s_disc
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
}	t_disc;

typedef struct s_cylinder_coll
{
	t_vector	proj_dir;
	t_vector	oc_proj;
	t_vector	oc;
	t_vector	coll_point;
	double		height_proj;
}	t_cylinder_coll;

typedef struct s_cap_collision
{
	t_vector	center;
	t_vector	cap_normal;
	t_vector	collision;
	double		t;
	double		denom;
}	t_cap_collision;

/*collision utils.c*/
t_vector		compute_normal_curved(t_vector collision_point, t_object *cy);
void			update_ray(t_ray *ray, t_object *object, double t);
double			calc_t(double *t, t_vector v1, t_vector v2, double r);

/*rotation.c*/
void			rotate_vector(t_vector *v, t_vector k, float theta);

/*printer.c*/
void			camera_light_ambient(t_object *c, t_object *l, t_object *a);
void			the_objects(t_object *o);
void			print_vector(t_vector v);
void			print_object(t_object *o);
void			print_help(void);

/*user_interface.c*/
void			select_object(t_object *object, t_data *data);

/*mouse.c*/
void			rt_mouse(void *param);

/*image.c*/
void			redraw(t_data *data);
void			reset_scene(t_data *data);

/*transformation.c*/
void			rotate_object(t_object *object, t_vector new_orientation);
void			translate_object(t_object *object, t_vector delta);

/*collision.c*/
int				sphere_collision(t_ray *ray, t_object *sp);
int				plane_collision(t_ray *ray, t_object *pl);
int				cylinder_collision(t_ray *ray, t_object *cy);

/*color.c*/
void			color_pixel(mlx_image_t *i, uint32_t pixel_c, int x, int y);

/*data*/
t_data			*init_data(char *file);
void			free_data(t_data *data);

/*errors.c*/
int				failure(char *message);

/*file_reader.c*/
int				read_objects(t_data *data);

/*keyhandler.c*/
void			keypress(mlx_key_data_t mlx_data, void *param);
void			rt_mouse(void *param);

/*keyhandler2.c*/
int				change_fov(mlx_key_data_t mlx_data, t_object *selected);
int				adjust_brightness(mlx_key_data_t mlx_data, t_object *selected);
int				resize_object(mlx_key_data_t mlx_data, t_object *selected);

/*lights.c*/
void			ambient_checks(int (**checks)(char *));
void			lights_checks(int (**checks)(char *));
void			create_light(t_light *light, t_ray *ray, t_vector collision);
uint32_t		set_lights(t_data *d, t_ray *r, t_vector coll, t_vector norm);

/*light_utils.c*/
double			in_the_shadow(t_vector coll, t_object *light, t_objarr *oj);
double			set_specular(t_vector norm, t_light *light);
double			set_diffuse(t_vector normal, t_light *light);

/*object_array.c*/
t_objarr		*init_objarr(size_t capacity);
int				add_object(t_data *data, char *line);
void			free_objarr(t_objarr *objarr);

/*object_parser.c*/
t_vector		parse_vector(char *str);
uint32_t		parse_color(char *str);

/*precalculations.c*/
t_image_plane	image_plane(t_object *camera);
void			set_precalculations(t_data *data);
void			precalculate_plane(t_object *plane, t_image_plane info);

/*sphere.c*/
void			sphere_checks(int (**checks)(char *));
int				assign_sphere(t_object *sphere, char **info);

/*plane.c*/
void			plane_checks(int (**checks)(char *));
int				assign_plane(t_object *plane, char **info);

/*cylinder.c*/
void			cylinder_checks(int (**checks)(char *));
int				assign_cylinder(t_object *cylinder, char **info);

/*camera.c*/
void			camera_checks(int (**checks)(char *));
int				assign_camera(t_object *camera, char **info);

/*object.c*/
t_type			get_type(char *line);
int				assign_ambient(t_object *ambient, char **info);
int				parse_object(t_object *object, char *line);
int				assign_light(t_object *light, char **info);
void			precalculate_plane(t_object *plane, t_image_plane info);
void			print_objects(t_data *data);

/*parser.c*/
double			parse_double(char *str);

/*ray.c*/
int				cast_ray(t_ray *ray, t_objarr *objarr);
void			raycast(t_data *data);
t_ray			get_ray(t_image_plane info, int x, int y);

/*utils.c*/
int				min(int a, int b);
int				max(int a, int b);
char			*trim_newline(char *str);
void			error_msg(t_data *data);

/*validation.c*/
int				validate(char *line);

/*validation_utils.c*/
int				is_double(char *ptr);
int				is_color(char *ptr);
int				is_vector(char *ptr);
int				is_int(char *ptr);

/*vector.c*/
t_vector		reflect_vector(t_vector light_dir, t_vector normal);
t_vector		vector(double x, double y, double z);
t_vector		cross_product(t_vector v1, t_vector v2);
double			dot(t_vector v1, t_vector v2);
int				is_normalized_vector(t_vector v);

/*vector_geometry.c*/
double			v_len(t_vector v);
double			v_dist(t_vector a, t_vector b);
t_vector		normalize_vector(t_vector v);

/*vector_math.c*/
t_vector		v_mul(double t, t_vector v);
t_vector		v_sub(t_vector v1, t_vector v2);
t_vector		v_sum(t_vector v1, t_vector v2);

#endif
