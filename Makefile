# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:15:18 by ansebast          #+#    #+#              #
#    Updated: 2024/10/05 10:17:45 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
BONUS = fdf_bonus
CFLAGS = -Wall -Wextra -Werror -g
LIBSRC = ./libft
MLXSRC = ./minilibx
LIBFT = $(LIBSRC)/libft.a
MLX = $(MLXSRC)/libmlx.a

SRC = fdf.c mlx_utils.c utils.c map.c projection.c hooks_utils.c line_utils.c validate_file.c
OBJS = $(SRC:.c=.o)

SRC_BONUS = fdf_bonus.c mlx_utils_bonus.c rotate_bonus.c utils_bonus.c map_bonus.c color_bonus.c projection_bonus.c \
		hooks_utils_bonus.c line_utils_bonus.c validate_file_bonus.c
OBJS_BONUS = $(SRC_BONUS:.c=.o)

INCLUDES = -I$(LIBSRC) -I$(MLXSRC)

LIBRARIES = -L$(LIBSRC) -lft -L$(MLXSRC) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	cc $(CFLAGS) $(OBJS) $(LIBRARIES) $(INCLUDES) -o $(NAME)

$(LIBFT):
	@make bonus -C $(LIBSRC)

$(MLX):
	@make -C $(MLXSRC)

bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX)
	cc $(CFLAGS) $(OBJS_BONUS) $(LIBRARIES) $(INCLUDES) -o $(BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C $(LIBSRC)
	@make clean -C $(MLXSRC)

fclean: clean
	rm -f fdf fdf_bonus
	@make fclean -C $(LIBSRC)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re