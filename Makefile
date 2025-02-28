#----------MAKEFILE----------#

NAME = cub3d

LIBFT = ../libft/libft.a

MLX_NAME = libmlx.a
MLX_PATH = minilibx-linux/
MLX = $(MLX_PATH)$(MLX_NAME)

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = 

OBJ = $(SRC: .c=.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compilation..."
	@make -sC ../libft
	@make -sC minilibx-linux
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) -lXext -lX11 -lm -lz
	@echo " is ready !"

clean:
	@echo "Clean..."
	@make clean -sC ../libft
	@make clean -sC minilibx-linux
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

.PHONY: all re clean fclean

