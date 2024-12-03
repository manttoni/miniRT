test:
	cc -g test.c src/*.c lib/mlx/libmlx.a -L/usr/X11/lib -lXext -lX11 -lm
