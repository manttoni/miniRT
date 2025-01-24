#ifndef DATA_H
# define DATA_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct	s_data
{
	t_node		*objects;
	mlx_t		*mlx;
	mlx_image_t		*image;
}	t_data;

/* Data */
t_data		*init_data(char *file);
void		free_data(t_data *data);

#endif
