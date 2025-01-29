NAME = testmain

SRC = test.c\
	../sources/object_noshape.c\
	../sources/object_parser.c\
	../sources/object_shape.c\
	../sources/object.c\
	../sources/parser.c\
	../sources/vector.c\
	../sources/utils.c

all:
	@cc -g -Wall -Werror -Wextra $(SRC) ../libft/libft.a -lm -o $(NAME)

clean:
	@rm -f $(NAME)