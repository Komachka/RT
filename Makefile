#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/03 17:21:13 by kzahreba          #+#    #+#              #
#    Updated: 2017/04/30 17:06:39 by kzahreba         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RTv1
CFLAGS = -O2
FILES = main.c vectors_1.c vectors_2.c intersection.c  intersection_objects.c \
paint_to_image.c basic_functions.c auxiliary_functions.c colors.c find_norm.c \
lightening_1.c lightening_2.c make_projection.c threads.c fill_objects_1.c \
fill_objects_2.c ft_atoi_base.c ft_strlen.c ft_putendl.c scenes.c
CC = gcc
OBJ = $(FILES:.c=.o)
FW = -lmlx -framework OpenGL -framework AppKit
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(FW)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
