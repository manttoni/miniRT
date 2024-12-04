#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/mlx/mlx.h"
# include "../lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <float.h>
# include <errno.h>

/* Keyboard */
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define ESCAPE_KEY 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define DELETE 65535

# define BACKGROUND_COLOR 0
# define BLUE 255
# define SALMON 0xFA8072
# define YELLOW 0xDFFF00
typedef struct	s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;
typedef struct	s_image
{
	void	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		focal_len;
}	t_image;

typedef struct	s_data
{
	t_node		*objects;
	int			x;
	int			y;
	void		*mlx;
	void		*win;
	t_image		*image;
	double		alpha;
	double		beta;
	double		gamma;
}	t_data;

typedef enum e_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;
/* type			ambient	camera	light	sphere	plane	cylinder
   color		YES		NO		NO*		YES		YES		YES
   brightness	YES		NO		YES		NO		NO		NO
   location		NO		YES		YES		YES		YES		YES
   orientation	NO		YES		NO		NO		YES		YES
   fov			NO		YES		NO		NO		NO		NO
   diameter		NO		NO		NO		YES		NO		YES
   height		NO		NO		NO		NO		NO		YES
   *) light has color in bonus */
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
	int			collision;
}	t_object;
typedef struct s_matrix
{
	double	val[3][3];
}	t_matrix;



t_node	*last_node(t_node *list);
int		add_node(t_node **list, t_node *new);
void	free_list(t_node *list);
t_node	*create_node(void *data);
double		vector_len(t_vector v);
t_vector	normalize_vector(t_vector v);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot_product(t_vector v1, t_vector v2);
t_vector	vector_substract(t_vector v1, t_vector v2);
t_vector	vector_multiply(double t, t_vector v);
void		print_vector(t_vector v);
t_vector	vector(double x, double y, double z);
t_matrix	transformation(double a, double b, double g);
t_vector	multi_matrix(t_vector v, t_matrix m);
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
int			sphere_collision(t_vector d, t_object *sphere, double *distance, t_vector light);
int			plane_collision(t_vector d, t_object *plane, double *distance);
int			cylinder_collision(t_vector d, t_object *cylinder, double *distance);

/* Shaped object creators */
t_object	*create_sphere(char **info);
t_object	*create_plane(char **info);
t_object	*create_cylinder(char **info);

/* Non-shaped object creators */
t_object	*create_ambient(char **info);
t_object	*create_camera(char **info);
t_object	*create_light(char **info);

/* Raycasting */
void		raycast(t_data *data);

/* Image */
t_image		*init_image(t_data *data);
void		color_pixel(t_data *data, int pixel_color, int x, int y);

/* Data */
t_data		*init_data(int x, int y, char *file);
void		free_data(t_data *data);

/* Keyhandler */
int			handle_close(void *param);
int			handle_key(int key, t_data *data);

/* Memory */
void		free_array(char **ar);

/* Files */
t_node		*read_objects(char *file);

/* Utils */
double		parse_double(char *str);
int			min(int a, int b);
char		*trim(char *str, char c);

/* Camera */
t_object	*get_camera(t_node *objects);

#endif
