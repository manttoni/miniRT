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



/* Image */


/* Keyhandler */


/* Memory */
// void		free_array(char **ar);

/* Files */
// t_node	*read_objects(t_data *data, char *file);
t_node	*read_objects(char *file);

/* Utils */
int			min(int a, int b);
int         max(int a, int b);
char	*trim(char *str, char c);
void	error_msg(t_data *data);

#endif
