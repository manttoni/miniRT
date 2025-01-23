#ifndef MINIRT_H
# define MINIRT_H

// # include "../lib/mlx/mlx.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include "../includes/linked_list.h"
# include "../includes/object.h"
# include "../includes/vector.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <float.h>
# include <errno.h>

/* Keyboard */
# define ESCAPE_KEY 65307

# define BACKGROUND_COLOR 0
# define BLUE 255
# define SALMON 0xFA8072
# define YELLOW 0xDFFF00
# define X 1000
# define Y 1000

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
}	t_data;

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
// void		free_array(char **ar);

/* Files */
t_node		*read_objects(char *file);

/* Utils */
double		parse_double(char *str);
int			min(int a, int b);
char		*trim(char *str, char c);

#endif
