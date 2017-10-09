NAME = RT
CC = gcc -Wall -Wextra -Werror
CFLAGS = -F./libraries/SDL -O3
JSON = ./libraries/JSON/cJSON.c
SDL_FLAGS =  -framework SDL2 -framework SDL2_image -framework SDL2_ttf
DSRC = ./src
SRC = main.c \
	  vectors_1.c \
	  vectors_2.c \
	  vectors_3.c \
	  intersection.c \
	  intersection_objects_1.c \
	  intersection_objects_2.c \
	  intersection_objects_3.c \
	  intersection_objects_4.c \
	  paint_to_image.c \
	  basic_functions.c \
	  auxiliary_functions.c \
	  colors_1.c \
	  colors_2.c \
	  find_norm_1.c \
	  find_norm_2.c \
	  find_norm_3.c \
	  lightening_1.c \
	  lightening_2.c \
	  lambert_phong_model_1.c \
	  toon_shading_model.c \
	  make_projection.c \
	  threads.c \
	  ft_standart_function_1.c \
	  ft_standart_function_2.c \
	  ft_key_hooks_1.c \
	  ft_key_hooks_2.c \
	  menu.c \
	  solving_equations.c \
	  json_get_scene.c \
	  json_valid_data.c \
	  json_valid_data_2.c \
	  json_valid_value.c \
	  json_validate_even_more_figures.c \
	  json_validate_figures.c \
	  json_validate_light.c \
	  json_validate_more_figures.c \
	  json_validate_object.c \
	  json_validate_objects.c \
	  json_validate_rest_figures.c \
	  json_validate_rtv_and_camera.c \
	  json_validate_textures_and_skybox.c \
	  json_validate_procedural_textures.c \
	  json_validate_vector_and_color.c \
	  filters.c \
	  animation.c \
	  mapping_texture.c \
	  perlin_noise_texture.c \
	  procedural_textures.c \
	  create_skybox.c

OBJ	= $(addprefix $(DSRC)/,$(SRC:.c=.o))
OBJJSON = $(JSON:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(OBJJSON)
	$(CC) $(CFLAGS) $(SDL_FLAGS) $(OBJJSON) $(OBJ)  -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(OBJJSON)

fclean: clean
	rm -rf $(NAME)

re: fclean all

sdl2:
	cp -r SDL2_image.framework ~/Library/Frameworks/
	cp -r SDL2.framework ~/Library/Frameworks/
	cp -r SDL2_ttf.framework ~/Library/Frameworks/
