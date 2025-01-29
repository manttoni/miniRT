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

# define BACKGROUND_COLOR 0xff000000
# define WHITE 0xffffffff
# define X 1200
# define Y 1200
# define RENDER_DISTANCE 2750

/* type			ambient	camera	light	sphere	plane	cylinder
   color		YES		NO		NO*		YES		YES		YES
   brightness	Y#include "../includes/object.h"
#include <fcntl.h>ES		NO		YES		NO		NO		NO
   location		NO		YES		YES		YES		YES		YES
   orientation	NO		YES		NO		NO		YES		YES
   fov			NO		YES		NO		NO		NO		NO
   diameter		NO		NO		NO		YES		NO		YES
   height		NO		NO		NO		NO		NO		YES
   *) light has color in bonus
   */

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
	struct s_object *next;
}	t_object;

/* Main struct*/
typedef struct	s_data
{
	t_object	*objects;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_data;

/* Data */
t_data		*init_data(char *file);
void		free_data(t_data *data);

/* Image */
void		color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y);
t_color		decompose_color(uint32_t color);
uint32_t	recompose_color(t_color color);
uint32_t	color_intensity(uint32_t color, double instensity);

int		handle_close(void *param);
void	keypress(mlx_key_data_t mlx_data, void *param);

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

void    raycast(t_data *data);

int		min(int a, int b);
int		max(int a, int b);
char	*trim(char *str, char c);
void	error_msg(t_data *data);

double		v_angle(t_vector a, t_vector b);
double		v_len(t_vector v);
t_vector	normalize_vector(t_vector v);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot_product(t_vector v1, t_vector v2);
t_vector	v_sum(t_vector v1, t_vector v2);
t_vector	v_sub(t_vector v1, t_vector v2);
t_vector	v_mul(double t, t_vector v);
void		print_vector(t_vector v);
t_vector	vector(double x, double y, double z);
double		v_dist(t_vector a, t_vector b);

t_object	*read_objects(char	*file);
char    *validate(char *line);

#endif
