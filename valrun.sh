cat valrun.sh
valgrind --leak-check=full --suppressions=MLX42.supp ./miniRT $1
