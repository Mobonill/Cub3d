
NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g #-fsanitize=address
#MLX = -L//home/mobonill/ub3d/mlx -lmlx -lXext -lX11
SRC =	srcs/parsing.c \
		srcs/utils.c \
		srcs/free.c \
		srcs/textures_and_colors.c \
		srcs/parsing_map.c \
		srcs/clean_file.c \
		srcs/main.c \
		srcs/utils_2.c \


RM = rm -f

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Llibft -lft $(MLX)

libft/libft.a :
	$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft
	
re: fclean all

.PHONY: all clean fclean re