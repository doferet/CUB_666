#----------MAKEFILE----------#

NAME = cub3d

LIBFT = ../libft/libft.a

MLX_NAME = libmlx.a
MLX_PATH = mlx/
MLX = $(MLX_PATH)$(MLX_NAME)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = main.c \
	parsing/parsing.c \
	utils/free_error.c \
	utils/utils.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	image/image.c \
	initialization/initialization.c \

OBJ = $(SRC: .c=.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compilation..."
	@make -sC ../libft
	@make -sC mlx
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) -lXext -lX11 -lm -lz
	@echo " is ready !"

clean:
	@echo "Clean..."
	@make clean -sC ../libft
	@make clean -sC mlx
	@$(RM) *.o
	@echo "Done !"

fclean: clean
	@echo "Remove..."
	@make fclean -sC ../libft
	@$(RM) $(NAME)
	@echo "Done !"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

re: fclean all

bonus:

.PHONY: all re clean fclean bonus

