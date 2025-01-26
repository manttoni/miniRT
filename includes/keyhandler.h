#ifndef KEYHANDLER_HPP
#define KEYHANDLER_HPP

# include "../MLX42/include/MLX42/MLX42.h"

int		handle_close(void *param);
void	keypress(mlx_key_data_t mlx_data, void *param);

#endif