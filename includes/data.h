#ifndef DATA_H
# define DATA_H

# include "image.h"

typedef struct	s_data
{
	t_node		*objects;
	int			x;
	int			y;
	mlx_t		*mlx;
	void		*win;
	t_image		*image;
}	t_data;

/* Data */
t_data		*init_data(int x, int y, char *file);
void		free_data(t_data *data);

/*Image*/
t_image		*init_image(t_data *data);

#endif
