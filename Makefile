test:
	cc -g test.c src/*.c lib/libft/libft.a lib/get_next_line/get_next_line.a lib/mlx/libmlx.a -L/usr/X11/lib -lXext -lX11 -lm
