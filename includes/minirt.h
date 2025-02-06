#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>
# include <float.h>
# include <float.h>

/* Defines */
# define EPSILON 0.001
# define BACKGROUND_COLOR 0xff000000
# define X 500
# define Y 500
# define FAILURE 1
# define SUCCESS 0
//# define RENDER_DISTANCE 150

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
    t_vector    direction;
    t_vector    coll_norm;
	t_vector	end;
    t_vector    start;
	double		distance;
    uint32_t    color;
}   t_ray;

typedef struct s_camera_info
{
	double			view_distance;
	t_vector		u;
	t_vector		v;
	t_ray			ray;
}	t_camera_info;

typedef struct	s_object
{
	t_type			type;
	uint32_t		color;
	double			brightness;;
	double			d;
	double			diameter;
	double			height;
	t_vector		location;
	t_vector		orientation;
	int				(*collisionf)(t_ray *, struct s_object);
	int				fov;
	t_camera_info	info;


}	t_object;

/*
	arr is malloced array of objects
	capacity is amount of memory allocated
	objects is amount of objects
*/
typedef struct s_objarr
{
	t_object	*arr;
	size_t		capacity;
	size_t		objects;
}	t_objarr;

typedef struct	s_data
{
	t_objarr	*objects;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_data;

void		print_object(t_object o);

/*collision.c*/
int			sphere_collision(t_ray *ray, t_object sp);
int			plane_collision(t_ray *ray, t_object pl);

/*color.c*/
void		color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y);

/*data*/
t_data		*init_data(char *file);
void		free_data(t_data *data);

/*errors.c*/
int			failure(char *message);

/*file_reader.c*/
t_objarr	*read_objects(char *file);

/*keyhandler.c*/
void		keypress(mlx_key_data_t mlx_data, void *param);

/*lights.c*/
uint32_t	set_lights(t_ray *ray, t_vector collision, t_vector normal, t_objarr *objarr);

/*object_array.c*/
t_objarr	*init_objarr(size_t capacity);
int 		add_object(t_objarr *objarr, char *line);
void		free_objarr(t_objarr *objarr);

/*object_getters.c*/
t_object	*get_object(t_objarr *objarr, t_type type);

/*object_parser.c*/
t_vector	parse_vector(char *str);
uint32_t	parse_color(char *str);

/*object.c*/
t_type		get_type(char *line);
int			assign_ambient(t_object *ambient, char **info);
int			parse_object(t_object *object, char *line);

/*parser.c*/
double		parse_double(char *str);

/*ray.c*/
int			cast_ray(t_ray *ray, t_objarr *objarr);
void		raycast(t_data *data);

/*utils.c*/
int			min(int a, int b);
int			max(int a, int b);
char		*trim_newline(char *str);
void		error_msg(t_data *data);

/*validation.c*/
char		*validate(char *line);

/*validation_utils.c*/
int			is_double(char *ptr);
int			is_color(char *ptr);
int			is_vector(char *ptr);
int			is_int(char *ptr);

/*vector.c*/
t_vector	reflect_vector(t_vector light_dir, t_vector normal);
void		print_vector(t_vector v);
t_vector	vector(double x, double y, double z);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot_product(t_vector v1, t_vector v2);
int			is_normalized_vector(t_vector v);

/*vector_geometry.c*/
double		v_len(t_vector v);
double		v_dist(t_vector a, t_vector b);
t_vector	normalize_vector(t_vector v);

/*vector_math.c*/
t_vector	v_mul(double t, t_vector v);
t_vector	v_sub(t_vector v1, t_vector v2);
t_vector	v_sum(t_vector v1, t_vector v2);

#endif
