NAME = miniRT

SRC_DIR = sources/

SRC = $(SRC_DIR)main.c\
	$(SRC_DIR)distance.c\
	$(SRC_DIR)color.c\
	$(SRC_DIR)object_getters.c\
	$(SRC_DIR)data.c\
	$(SRC_DIR)file_reader.c\
	$(SRC_DIR)keyhandler.c\
	$(SRC_DIR)linked_list.c\
	$(SRC_DIR)object_noshape.c\
	$(SRC_DIR)object_parser.c\
	$(SRC_DIR)object_shape.c\
	$(SRC_DIR)object.c\
	$(SRC_DIR)parser.c\
	$(SRC_DIR)ray.c\
	$(SRC_DIR)utils.c\
	$(SRC_DIR)vector.c\

FLAGS = -Wall -Werror -Wextra -g -O2
OFLAGS = -ldl -lglfw -pthread -lm
MAKEFLAGS += --no-print-directory
HEADS = -I. $(MLX_HEAD) -I$(LIBFT_DIR)

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft
LIBFT_LINK = -L$(LIBFT_DIR) -lft
LIBFT_INC = -I$(LIBFT_DIR)/includes

OBJ_DIR = objects/
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_DIRS = $(sort $(dir $(OBJS)))

MLX = ./MLX42
MLX_HEAD = -I $(MLX)/include
LIBMLX = $(MLX)/build/libmlx42.a

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ_DIRS) $(OBJS)
		@cc $(OBJS) $(LIBFT) $(LIBMLX) $(OFLAGS) -o $(NAME) > /dev/null
		@echo "\n\033[0;32mLet's mini!\033[0m\n"

$(LIBFT):
		@make -C $(LIBFT_DIR)
		@echo "\n\033[0;32mLibft ready\033[0m\n"

$(LIBMLX):
		@if [ ! -d "$(MLX)" ]; then \
			echo "\n\033[0;33mCloning MLX...\033[0m\n"; \
			git clone https://github.com/codam-coding-college/MLX42.git $(MLX) > /dev/null 2>&1; \
		fi
		@if [ ! -d "$(MLX)/build" ]; then \
			cmake $(MLX) -B $(MLX)/build > /dev/null; \
		fi
		@make -C $(MLX)/build -j4 > /dev/null
		@echo "\n\033[0;32mMLX ready\033[0m\n"

$(OBJ_DIRS):
		@mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@cc $(FLAGS) $(LIBFT_INC) -c $< -o $@ $(HEADS)
clean:
		@rm -rf $(OBJ_DIR)
		@rm -rf $(MLX)/build
		@make -C $(LIBFT_DIR) clean

fclean: clean
		@rm -f $(NAME)
		@make -C $(LIBFT_DIR) fclean
		@rm -rf $(MLX)
		@echo "\n\033[0;31mAll is gone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft
