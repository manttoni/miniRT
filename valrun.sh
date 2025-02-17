echo "Running valgrind in quiet mode with --leak-check=full and suppression file"
valgrind -q --leak-check=full --suppressions=MLX42.supp ./miniRT $1
