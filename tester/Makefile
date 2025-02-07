NAME = testmain

SRC_DIR := ../sources
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_FILES := $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/data.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/keyhandler.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/color.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/ray.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/light.c, $(SRC_FILES))

FLAGS = -Wall -Werror -Wextra -g
OFLAGS = -Iinclude -ldl -lglfw -pthread -lm

all:
	cc $(FLAGS) $(OFLAGS) test.c $(SRC_FILES) ../libft/libft.a -lm -o $(NAME)

clean:
	@rm -f $(NAME)
