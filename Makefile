# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:15:18 by ansebast          #+#    #+#              #
#    Updated: 2024/10/04 13:17:41 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -Wall -Wextra -Werror -g
LIBSRC = ./libft
MLXSRC = ./minilibx
LIBFT = $(LIBSRC)/libft.a
MLX = $(MLXSRC)/libmlx.a
SRC = fdf.c mlx_utils.c rotate.c utils.c map.c color.c projection.c hooks_utils.c line_utils.c validate_file.c
OBJS = $(SRC:.c=.o)

INCLUDES = -I$(LIBSRC) -I$(MLXSRC)

LIBRARIES = -L$(LIBSRC) -lft -L$(MLXSRC) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	cc $(CFLAGS) $(OBJS) $(LIBRARIES) $(INCLUDES) -o $(NAME)

$(LIBFT):
	@make bonus -C $(LIBSRC)

$(MLX):
	@make -C $(MLXSRC)

clean:
	rm -f $(OBJS)
	@make clean -C $(LIBSRC)
	@make clean -C $(MLXSRC)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBSRC)

re: fclean all

.PHONY: all clean fclean re