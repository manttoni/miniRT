NAME = testmain

SRC_DIR := ../sources
SRC = 	errors.c \
		object_parser.c \
		object.c \
		parser.c \
		utils.c \
		validation_utils.c \
		validation.c \
		vector_geometry.c \
		vector_math.c \
		vector.c \
		collision.c

SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRC))


FLAGS = -Wall -Werror -Wextra -g
#OFLAGS = -Iinclude -ldl -lglfw -pthread -lm

all:
	@cc $(FLAGS) test.c $(SRC_FILES) ../libft/libft.a -lm -o $(NAME)

clean:
	@rm -f $(NAME)
