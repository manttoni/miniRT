NAME = libftprintf.a

SRCS = ft_printf.c \
	   put_functions/ft_putchar.c \
	   put_functions/ft_putstr.c \
	   put_functions/ft_putptr.c \
	   put_functions/ft_putdec.c \
	   put_functions/ft_putint.c \
	   put_functions/ft_putuint.c \
	   put_functions/ft_puthex.c \
	   put_functions/ft_puthex_caps.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	cc -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
