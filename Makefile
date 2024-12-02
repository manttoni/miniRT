test:
	cc -g test.c src/data.c src/vector.c src/sphere.c src/linked_list.c src/ray.c src/image.c lib/mlx/libmlx.a -L/usr/X11/lib -lXext -lX11 -lm
