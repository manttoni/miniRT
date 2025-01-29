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

/* Defines */
# define EPSILON 0.001
# define BACKGROUND_COLOR 0xff000000
# define SHADOW_COLOR 0xffffffff
# define WHITE 0xffffffff
# define X 750
# define Y 750
# define RENDER_DISTANCE 150

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
    double      distance;
    uint32_t    color;
    t_vector    location;
}   t_ray;


typedef struct s_camera_info
{
	unsigned int	view_distance;
	t_vector		u;
	t_vector		v;
	t_ray			ray;
}	t_camera_info;

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct	s_image
{
	mlx_image_t	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		focal_len;
}	t_image;

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
	double			d;
	struct s_object *next;
}	t_object;

typedef struct	s_data
{
	t_object	*objects;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_data;

/* Validation */
char    		*validate(char *line);
int				is_double(char *ptr);
int				is_int(char *ptr);
int				is_color(char *ptr);
int				is_vector(char *ptr);

/* Data */
t_data			*init_data(char *file);
void			free_data(t_data *data);

/* Image & Color */
void			color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y);
t_color			decompose_color(uint32_t color);
uint32_t		recompose_color(t_color color);
uint32_t		color_intensity(uint32_t color, double instensity);

/* Keyhandlers */
int				handle_close(void *param);
void			keypress(mlx_key_data_t mlx_data, void *param);

/* Object list */
t_object		*last_object(t_object *list);
int				add_node(t_object **list, t_object *new);
void			free_list(t_object *list);
t_object		*create_node(char *line);
t_object		*read_objects(char	*file);
void			print_list(t_object *list);

/* Raytracing */
double  		closest(t_ray *ray, t_object *objects);
void    		raycast(t_data *data);

/* Objects */
void			print_object(t_object *o);
t_object		*get_object(t_object *objects, t_type type);
t_camera_info 	image_plane(t_object *camera);

/* Object parsers */
int				parse_object(t_object	*object, char *line);
int				parse_orientation(char *str, t_vector *orientation);
int				parse_location(char *str, t_vector *location);
int				parse_color(char *str);
t_type			get_type(char *line);

/* Shaped object creators */
void			create_sphere(t_object *object, char **info);
void			create_plane(t_object *object, char **info);
void			create_cylinder(t_object *object, char **info);

/* Non-shaped object creators */
void			create_ambient(t_object *object, char **info);
void			create_camera(t_object *object, char **info);
void			create_light(t_object *object, char **info);

/* Utils */
double			parse_double(char *str);
int				min(int a, int b);
int				max(int a, int b);
char			*trim(char *str, char c);

/* Errors */
void			error_msg(t_data *data);

/* Vectors */
double			v_angle(t_vector a, t_vector b);
double			v_len(t_vector v);
t_vector		normalize_vector(t_vector v);
t_vector		cross_product(t_vector v1, t_vector v2);
double			dot_product(t_vector v1, t_vector v2);
t_vector		v_sum(t_vector v1, t_vector v2);
t_vector		v_sub(t_vector v1, t_vector v2);
t_vector		v_mul(double t, t_vector v);
void			print_vector(t_vector v);
t_vector		vector(double x, double y, double z);
double			v_dist(t_vector a, t_vector b);

#endif