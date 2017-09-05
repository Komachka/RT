#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/03 17:21:13 by kzahreba          #+#    #+#              #
#    Updated: 2017/08/06 20:20:42 by kzahreba         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RT
CFLAGS =  -O3
MLXSRC = libraries/minilibx_macos
LIBMLX = libraries/minilibx_macos/libmlx.a
DSRC = ./src
SRC = main.c \
	vectors_1.c \
	vectors_2.c \
	intersection.c \
	intersection_objects.c \
	paint_to_image.c \
	basic_functions.c \
	auxiliary_functions.c \
	colors.c find_norm.c \
	lightening_1.c \
	lightening_2.c \
	lambert_phong_model.c \
	toon_shading_model.c \
	make_projection.c \
	threads.c \
	fill_objects_1.c \
	fill_objects_2.c \
	ft_atoi_base.c \
	ft_strlen.c \
	ft_putendl.c \
	scenes.c
CC = gcc
OBJ	= $(addprefix $(DSRC)/,$(SRC:.c=.o))
FW = -framework OpenGL -framework AppKit
all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLXSRC)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBMLX) $(FW)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
