#----------MAKEFILE----------#

NAME = cub3d

LIBFT = libft/libft.a

MLX_NAME = libmlx.a
MLX_PATH = mlx/
MLX = $(MLX_PATH)$(MLX_NAME)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

INC = -Iinclude -Ilibft

SRC = src/main.c \
	src/parsing/parsing.c \
	src/parsing/check_wall.c \
	src/parsing/check_color.c \
	src/parsing/check_player.c\
	src/parsing/p_utils.c \
	src/parsing/check_datafile.c \
	src/parsing/check_textures.c \
	src/init/init.c \
	src/utils/free_error.c \
	src/utils/utils.c \
	libft/get_next_line/get_next_line.c \
	libft/get_next_line/get_next_line_utils.c \
	src/image/image.c \
	src/maths/maths.c \
	src/maths/textures.c \
	src/maths/player_move.c \
	src/maths/render.c \

OBJ_DIR = build
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

RM = rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	@echo "Compilation..."
	@make -sC libft
	@make -sC mlx
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(INC) -lXext -lX11 -lm 
	@echo "Cub3D is ready !"

clean:
	@echo "Clean..."
	@make clean -sC libft
	@make clean -sC mlx
	@$(RM) $(OBJ_DIR)
	@echo "Done !"

fclean: clean
	@echo "Remove..."
	@make fclean -sC libft
	@$(RM) $(NAME)
	@echo "Done !"

re: fclean all

.PHONY: all re clean fclean

