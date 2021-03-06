define generate_file
    @echo "Compiling.."
    @echo '$(1)'
endef

NAME = RT
CC = gcc -Wall -Wextra -Werror
CFLAGS = -F./libraries/SDL -O3
JSON = ./libraries/JSON/cJSON.c
SDL_FLAGS =  -framework SDL2 -framework SDL2_image -framework SDL2_ttf
DSRC = ./src
SRC = main.c \
	  vectors_1.c \
	  vectors_2.c \
	  intersection.c \
	  intersection_objects_1.c \
	  intersection_objects_2.c \
	  intersection_objects_3.c \
	  intersection_objects_4.c \
	  intersection_objects_5.c \
	  intersection_objects_6.c \
	  paint_to_image.c \
	  basic_functions.c \
	  auxiliary_functions.c \
	  free_rtv.c \
	  colors_1.c \
	  colors_2.c \
	  find_norm_1.c \
	  find_norm_2.c \
	  find_norm_3.c \
	  find_norm_4.c \
	  lightening_1.c \
	  lightening_2.c \
	  lambert_phong_model_1.c \
	  lambert_phong_model_2.c \
	  toon_shading_model.c \
	  make_projection.c \
	  make_projection_2.c \
	  threads.c \
	  ft_standart_function_1.c \
	  ft_standart_function_2.c \
	  ft_standart_function_3.c \
	  ft_key_hooks_1.c \
	  ft_key_hooks_2.c \
	  menu_1.c \
	  menu_2.c \
	  menu_3.c \
	  solving_equations.c \
	  solving_equations_2.c \
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
	  json_validate_polygon.c \
	  json_validate_rest_figures.c \
	  json_validate_rtv_and_camera.c \
	  json_validate_textures_and_skybox.c \
	  json_validate_procedural_textures.c \
	  json_validate_vector_and_color.c \
	  filters_1.c \
	  filters_2.c \
	  filters_3.c \
	  filters_4.c \
	  animation.c \
	  mapping_texture.c \
	  perlin_noise_texture.c \
	  procedural_textures.c \
	  create_skybox.c \
	  textures.c \


OBJ	= $(addprefix $(DSRC)/,$(SRC:.c=.o))
OBJJSON = $(JSON:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(OBJJSON)
	@$(CC) $(CFLAGS) $(SDL_FLAGS) $(OBJJSON) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compiling.."  $<


clean:
	@echo "Cleaning.."
	@rm -rf $(OBJ) $(OBJJSON)

fclean: clean
	@echo "Cleaning.."
	@rm -rf $(NAME)

re: fclean all

sdl2:
	cp -r libraries/SDL/SDL2_image.framework ~/Library/Frameworks/
	cp -r libraries/SDL/SDL2.framework ~/Library/Frameworks/
	cp -r libraries/SDL/SDL2_ttf.framework ~/Library/Frameworks/
