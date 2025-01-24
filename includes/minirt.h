#ifndef MINIRT_H
# define MINIRT_H

// # include "../lib/mlx/mlx.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include "linked_list.h"
# include "object.h"
# include "./vector.h"
# include "./ray.h"
# include "data.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <float.h>
# include <errno.h>
# include <fcntl.h>

# define BACKGROUND_COLOR 0xff000000
# define X 1500
# define Y 1500

/* Image */
void		color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y);

/* Keyhandler */
int		handle_close(void *param);
void	keypress(mlx_key_data_t mlx_data, void *param);

/* Memory */
// void		free_array(char **ar);

/* Files */
// t_node	*read_objects(t_data *data, char *file);
t_node	*read_objects(char *file);

/* Utils */
<<<<<<< HEAD
int			min(int a, int b);
int         max(int a, int b);
char		*trim(char *str, char c);
=======
int		min(int a, int b);
char	*trim(char *str, char c);
void	error_msg(t_data *data);
>>>>>>> master

#endif
