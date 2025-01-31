NAME = testmain

SRC_DIR := ../sources
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_FILES := $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/data.c, $(SRC_FILES))
SRC_FILES := $(filter-out $(SRC_DIR)/keyhandler.c, $(SRC_FILES))

all:
	@cc -g -Wall -Werror -Wextra test.c $(SRC_FILES) ../libft/libft.a -lm -o $(NAME)

clean:
	@rm -f $(NAME)