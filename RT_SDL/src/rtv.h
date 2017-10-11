/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:36:45 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/04 19:40:46 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> //для чого це?
# include <time.h> //для чого це?
# include "SDL2_ttf/SDL_ttf.h"
# include "SDL2/SDL.h"
# include "SDL2_image/SDL_image.h"
# include "../libraries/JSON/cJSON.h"

// # define WINDOW_WIDTH 1000 //взнати що це?
// # define WINDOW_HEIGHT (WINDOW_WIDTH)

# define COUNT 6

# define WX 1000
# define WY 1000

# define WIDTH 1400
# define HEIGHT 1000
# define SCENSES 6
# define FILTERWIDTH 3 //чи використовується?
# define FILTERHEIGHT 3

# define NUM_THREADS 8
# define BIAS 0.001
# define PRECISION 0.000001f

# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))
# define VAR_INT(x, y) int x = y
# define TO_RAD(x) ((M_PI * (x)) / 180.0)

enum {X, Y, Z};
enum {OFF, ON};

/*
** lightening models
*/
enum {LAMBERT, CARTOON};

/*
** camera  types
*/
enum {STANDART, FISHEYE};

/*
**	textures
*/
enum {PERLIN, MAPPING, PLASMA, CONTOURS, CAUSTIC,  JUPITER};

/*
** light types
*/
enum {DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT};

/*
** figure types
*/
enum {SPHERE, PLANE, CYLINDER, CONE, TORUS, TRIANGLE, DISC, ELLIPSOID, \
	PARABOLOID, LIMITED_CYLINDER, LIMITED_CONE, LIMITED_PARABOLOID, \
	LIMITED_SPHERE, PLANE_WITH_HOLE, DISC_WITH_HOLE};

/*
**  структури, які не використовуєте повидаляти !!!
*/

typedef struct	s_scene //вияснити що це?
{
	int	number;
}				t_scene;

typedef struct	s_scene_menu_box
{
	int			number;
	SDL_Rect	menu_box_rect;
	SDL_Texture	*menu_box_image;
}				t_scene_menu_box;

typedef struct	s_scene_menu
{
	int					menu_size; // need to del
	int					menu_weight;
	int					menu_hight;
	SDL_Rect			menu_scene_rect;
	t_scene_menu_box	*menu_boxes;
}			t_scene_munu;


/*
** structures for menu
*/

typedef struct	s_box
{
	SDL_Rect	rect;
	SDL_Texture	*scene;
}				t_box;



typedef struct	s_menu
{
	SDL_Window		*window;
	unsigned int	window_id;
	SDL_Renderer	*renderer;
	SDL_Event		e;

	t_box			boxes[SCENSES+1]; // for scene and one for beckground

}				t_menu;

/*
** basic structures
*/

typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

typedef	struct	s_color
{
	double		r;
	double		g;
	double		b;
	double		al;
}				t_color;

typedef struct	s_ray
{
	t_vect		origin;
	t_vect		dir;
}				t_ray;

typedef	struct	s_camera
{
	int			type;
	double		fisheye_angle;
	t_vect		pos;
	double		rotate[3];
	double		image_aspect_ratio;
	double		scale;
	double		lk_dir;
}				t_camera;

typedef	struct	s_material
{
	int 		color;
	t_color		cl;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double 		refraction;
}				t_material;

typedef struct	s_light
{
	int		type;
	t_vect	pos;
	t_color	intensity;
	t_vect	direction;
	double	k_const;
	double	k_linear;
	double	k_quadratic;
	double	outer_cone;
	double	inner_cone;
	double	epsilon;
}				t_light;

typedef struct	s_additional
{
	int			figure;
	t_vect		point;
	t_vect		norm;
	t_ray		light_ray;
	t_ray		rev_light_ray;
	t_ray		primary_ray;
	t_material	mat;
	double		attenuation;
	t_color		a;
	t_color		d;
	t_color		s;
	t_color		r;
	t_color		refr;
	double		diff;
	double		len;
	double		spot_coef;
}				t_additional;

/*
**	figures structures
*/
typedef struct	s_sphere
{
	t_vect		pos;
	double		r;
}				t_sphere;

typedef struct	s_plane
{
	t_vect		norm;
	t_vect		point;
}				t_plane;

typedef struct	s_cylinder
{
	t_vect		pos;
	t_vect		dir;
	double		r;
}				t_cylinder;

typedef struct	s_cone
{
	t_vect		pos;
	t_vect		dir;
	double		rad;
}				t_cone;

typedef struct	s_torus
{
	t_vect	pos;
	t_vect	dir;
	double	maj_r;
	double	min_r;
}				t_torus;

typedef struct	s_triangle
{
	t_vect	a;
	t_vect	b;
	t_vect	c;
	t_vect	v0;
	t_vect	v1;
	t_vect	norm;
}				t_triangle;

typedef struct	s_disc
{
	t_vect	pos;
	t_vect	norm;
	double	r;
}				t_disc;

typedef struct	s_ellipsoid
{
	t_vect	pos;
	double	size_x;
	double	size_y;
	double	size_z;
}				t_ellipsoid;

typedef struct	s_paraboloid
{
	t_vect	extremum;
	t_vect	dir;
	double	k;
}				t_paraboloid;


typedef struct	s_limited_cylinder
{
	t_vect	p1;
	t_vect	p2;
	t_vect	p1_norm;
	t_vect	p2_norm;
	t_vect	dir;
	double	h;
	double	r;
	int		caps;
}				t_limited_cylinder;

typedef struct	s_limited_cone
{
	t_vect	pos;
	t_vect	dir;
	double	rad;
	double	r1;
	double	r2;
	double	h1;
	double	h2;
	t_vect	p1;
	t_vect	p2;
	t_vect	p1_norm;
	t_vect	p2_norm;
	int		caps;
}				t_limited_cone;

typedef struct	s_limited_sphere
{
	t_vect	pos;
	double	r;
	t_vect	cut_dir;
	t_vect	p1;
	t_vect	p2;
	double	cut_r;
	int		caps;
}				t_limited_sphere;

typedef struct	s_limited_paraboloid
{
	t_vect	extremum;
	t_vect	dir;
	t_vect	bottom;
	double	k;
}				t_limited_paraboloid;

typedef struct s_plane_with_hole
{
	t_vect		norm;
	t_vect		point;
	int 		holes_num;
	t_disc		*hole;
}				t_plane_with_hole;

typedef struct s_disc_with_hole
{
	t_disc		disc;
	t_disc 		hole;
}				t_disc_with_hole;

/*
** textures
*/

typedef struct s_texture
{
	int 		type;
	void 		*tx_struct;
	void 		(*creating_texture)(t_additional *, void *);
}				t_texture;

typedef struct s_mapping_texture
{
	int 		*arr;
	int 		w;
	int 		h;
	char 		*img_path;
	SDL_Surface *srf;
}				t_mapping_texture;

typedef struct s_perlin_texture
{
	int   		octaves;
	double 		amplitude;
	double 		persistence;
	double		exponent;
	t_vect 		frequency;
	t_vect 		frequency_att; // затухання частоти
}				t_perlin_texture;

typedef struct  s_plasma_texture
{
	t_color 	frequency;
	t_color 	phase;
}				t_plasma_texture;

typedef struct  s_contours_texture
{
	t_color 	contour;
	t_color 	background;
	double		t;
	double 		frequency;
}				t_contours_texture;

typedef struct s_caustic_texture
{
	t_color 	color_1;
	t_color 	color_2;
	double 		sharpness;
	double		coverage;
}				t_caustic_texture;

typedef struct s_jupiter_texture
{
	double 		vortices;
	double 		bands;
	double 		perturbations;
	double 		bands_fade;
	t_color 	band;
	t_color 	background;
}				t_jupiter_texture;

/*
** skybox
*/

typedef	struct s_skybox
{
	t_vect 		pos;
	double		r;
	t_color 	cl;
	int 		texturing;
	t_texture 	texture;
}				t_skybox;

/*
** object's struct
*/
typedef struct	s_figure
{
	int			id;
	int 		texturing;
	void		*object;
	t_material	material;
	t_texture	texture;
	int			(*intersection_object)(t_ray *, void *, double *);
	t_vect		(*norm_vector)(void *, t_vect *);
}				t_figure;

/*
** filters
*/
typedef struct	s_filter
{
	int			black_and_white;
	int			blur;
	int			glass;
	int			emboss;
	int			sepia;
	int			negative;
	int			romanets;
	//SDL_Color	sdl_col_with_filter[WX][WY];
	SDL_Color	**sdl_col_with_filter;
}				t_filter;

/*
** main structure
*/
typedef struct	s_rtv
{
	cJSON			*obj;
	SDL_Window		*window;
	unsigned int	window_id;
	SDL_Texture		*sdl_texture_render;
	SDL_Texture		*sdl_texture_loading[54];
	SDL_Renderer	*renderer;
	SDL_Event		e;
	int				len; //використовуємо?
	//SDL_Color		s_c[WX][WY];
	SDL_Color		**s_c;
	SDL_Surface		*picture;
	SDL_Surface		*surface_main;
	SDL_Rect		rect_rt;
	SDL_Rect		display_rect;
	SDL_Rect		hooks_rect;
	SDL_Surface		*surface;
	SDL_Texture		*surface_texture;
	SDL_Texture		*hooks;
	int				light_num;
	int				figure_num;
	int				lightening;
	int				light_model;
	int				recursive_depth;
	int				bg_color;
	int				samples_grid;
	int 			samples;
	int				samples_per_pixel;
	double			delta_aliasing;
	double			air_coef; // треба буде видалити, якщо не зміню заломлення
	double			expos;
	t_filter		filter;
	t_color			background_color;
	t_camera		cam;
	t_figure		*objects;
	t_light			*l;
	t_color			global_light;
	int 			sk;
	t_skybox 		skybox;
}					t_rtv;

/*
** additionl structures
*/
typedef struct	s_thred
{
	t_rtv		*rtv1;
	int			y_start;
	int 		y_end;
	t_ray		ray;
	int			index;
}				t_thred;

typedef struct	s_final_color
{
	t_color	a;
	t_color	d;
	t_color	s;
}				t_final_color;

/*
**	structures for solving equations
*/
typedef struct	s_cubic_resv
{
	double	p;
	double	q;
	double	r;
	double	z;
}				t_cubic_resv;

typedef struct	s_equation
{
	double	a;
	double	b;
	double	c;
	double	discr;
	double	sqdiscr;
	double	root[4];
}				t_equation;

typedef struct	s_quartic_eq
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	e;
	double	root[4];
}				t_quartic_eq;

typedef struct s_tor
{
	double			u;
	double			v;
	double			a;
	double			b;
	double			c;
	double			d;
}				t_tor;




/*
** actions with vectors
*/
double			vector_dot_product(t_vect *v1, t_vect *v2);
t_vect 			vector_cross_product(t_vect *a, t_vect *b);
t_vect			vector_add(t_vect *v1, t_vect *v2);
t_vect			vector_substract(t_vect *v1, t_vect *v2);
t_vect			vector_mult(double i, t_vect *v1);
double			vector_length(t_vect *v);
t_vect			normalize_vector(t_vect *v1);
void			vector_rewrite(t_vect *v1, t_vect *v2);
t_vect			reflected_vector(t_vect *v, t_vect *norm);
t_vect			refracted_vector(t_vect *norm, t_vect *incident, double refraction_coef);
t_vect			change_vector_direction(t_vect *v);
t_vect			create_vector(double x, double y, double z);
void 			set_zero_vect(t_vect *v);
t_vect			project_point_on_plane(t_vect *point, t_vect *pl_point, t_vect *pl_norm);
t_vect			mult_vectors_coordinates(t_vect *a, t_vect *b);
/*
** intersection functions for objects
*/
int				intersection_sphere(t_ray *r, void *sphere, double *t);
int				intersection_cone(t_ray *r, void *cone, double *t);
int				intersection_plane(t_ray *r, void *plane, double *t);
int				intersection_cylinder(t_ray *r, void *cylinder, double *t);
int				intersection_torus(t_ray *r, void *torus, double *t);
int 			intersection_triangle(t_ray *r, void *triangle, double *t);
int				intersection_disc(t_ray *r, void *disc, double *t);
int				intersection_ellipsoid(t_ray *r, void *ellipsoid, double *t);
int				intersection_paraboloid(t_ray *r, void *paraboloid, double *t);
int 			intersection_limited_cylinder(t_ray *r, void *disc, double *t);
int 			intersection_limited_cone(t_ray *r, void *disc, double *t);
int 			intersection_limited_paraboloid(t_ray *r, void *disc, double *t);
int 			intersection_limited_sphere(t_ray *r, void *disc, double *t);
int 			intersection_plane_with_hole(t_ray *r, void *disc, double *t);
t_color			intersection(t_rtv *rtv, t_ray *r);
t_vect			intersection_point(double t, t_ray *r);
int				complicated_intersection(t_rtv *rtv, t_ray *r, double *point);
int 			intersection_disc_with_hole(t_ray *r, void *disc, double *t);

/*
** calculating norm vectors for objects
*/
t_vect			sphere_norm_vector(void *obj, t_vect *point);
t_vect			plane_norm_vector(void *obj, t_vect *point);
t_vect			cylinder_norm_vector(void *obj, t_vect *point);
t_vect			cone_norm_vector(void *obj, t_vect *point);
t_vect			torus_norm_vector(void *obj, t_vect *point);
t_vect 			triangle_norm_vector(void *obj, t_vect *point);
t_vect			disc_norm_vector(void *obj, t_vect *point);
t_vect			ellipsoid_norm_vector(void *obj, t_vect *point);
t_vect 			paraboloid_norm_vector(void *obj, t_vect *point);
t_vect 			limited_cylinder_norm_vector(void *obj, t_vect *point);
t_vect 			limited_cone_norm_vector(void *obj, t_vect *point);
t_vect 			limited_paraboloid_norm_vector(void *obj, t_vect *point);
t_vect 			limited_sphere_norm_vector(void *obj, t_vect *point);
t_vect 			plane_with_hole_norm_vector(void *obj, t_vect *point);
t_vect			find_norm(t_rtv *rtv, int figure, t_vect *point, t_vect *r_dir);
t_vect			disc_with_hole_norm_vector(void *obj, t_vect *point);

/*
** colorizing
*/
t_color			calculate_color(double i, t_color *c);
t_color			average_color(t_color *lights, int light_num);
void			paint_image(t_rtv *r, int x, int y, t_color cl);
t_color			colorizing(t_rtv *rtv, int figure, double t, t_ray *r, int recursive_depth);
t_color			create_color_struct(double r, double g, double b, double a);
t_color			mult_color_coefs(t_color a, t_color b);
t_color 		proportional_color_distribution(t_color *cl1, t_color *cl2, double p1);
void 			set_zero_color(t_color *cl);
t_color			create_color(char *hex);
t_color 		parse_color(int color);
void 			correct_exposure(t_rtv *rtv, t_color *color);
t_color		create_background_color(t_rtv *rtv, t_ray *r);

/*
** lightening models
*/
t_color 		lambert_phong_model(t_rtv *rtv, t_additional *s, int recursive_depth);
t_color			toon_shading_model(t_rtv *rtv, t_additional	*s);

/*
**  actions with light
*/
void			create_light_ray(t_light *l, t_additional *st);
int				shadow(t_rtv *rtv, t_ray *r, double light);


/*
** textures
*/
void 			uploading_textures(t_rtv *rtv); //- дописати на SDL
void 			free_textures(t_rtv *rtv);
void 			sphere_mapping_texture(t_additional *s, void *t);
double		 	calculate_perlin_noise(t_vect point);
void			perlin_noise_texture(t_additional *st, void *texture_st);
void 			plasma_texture(t_additional *s, void *t);
void 			contours_texture(t_additional *s, void *t);
void 			caustic_texture(t_additional *s, void *t);
void 			jupiter_texture(t_additional *s, void *t);
t_color 		creating_skybox(t_rtv *rtv, t_ray *r);

/*
** filters
*/
void 			copy_to_filter(t_rtv *rtv);
void 			create_b_n_w_filter(t_rtv *rtv);
void 			create_blur_filter(t_rtv *rtv, double red, double green, double blue);
void 			create_emboss_filter(t_rtv *rtv, double red, double green, double blue);
void 			create_glass_filter(t_rtv *rtv);
void 			create_sepia_filter(t_rtv *rtv, int red, int green, int blue);
void 			create_negative_filter(t_rtv *rtv);
void 			create_sromanets(t_rtv *rtv);

/*
** basic functions
*/
void			basic_function(t_rtv *rtv);
void			threads(t_rtv *rtv);
void			*make_projection(void *k);

/*
** auxiliary functions
*/
double			min(double i, double j);
int				check_solving(double *t, double t0);
int				quadratic_equation(t_equation *n);
int 			quartic_equation(t_quartic_eq *n);
double			select_value(double *array, int len);
t_vect			adding_bias(t_vect *point, t_vect *dir);
void			delstruct(t_rtv *rtv);
void    del_arrey(void **arrey, int size);
void malloc_sdl_colour(t_rtv *rtv);



int				ft_atoi_base(const char *str, int base);
size_t			ft_strlen(char const *str);
void			ft_putendl(char const *s);
char			*join(const char *str1, const char *str2);
_Bool			cmp(const char *str1, const char *str2);

/*
** managing errors
*/

void			malloc_error(void);
void			put_error(const char *message, const char *second_message);

/*
** JSON
*/

void			get_scene(const char *name, t_rtv *rtv);
char			*validate_rtv(cJSON *obj, t_rtv *rtv);
char			*validate_camera(cJSON *obj, t_camera *cam);
char			*validate_skybox(cJSON *obj, t_rtv *rtv);
char			*validate_light(cJSON *obj, t_rtv *rtv);
char			*validate_objects(cJSON *obj, t_rtv *rtv);
char			*validate_object(cJSON *object, t_figure *figure, int id);
char			*validate_sphere(cJSON *tmp[], t_figure *figure);
char			*validate_cylinder(cJSON *tmp[], t_figure *figure);
char			*validate_cone(cJSON *tmp[], t_figure *figure);
char			*validate_torus(cJSON *tmp[], t_figure *figure);
char			*validate_plane(cJSON *tmp[], t_figure *figure);
char			*validate_plane_with_hole(cJSON *tmp[], t_figure *figure);
char			*validate_triangle(cJSON *tmp[], t_figure *figure);
char			*validate_disc(cJSON *tmp[], t_figure *figure);
char			*validate_disc_with_hole(cJSON *tmp[], t_figure *figure);
char			*validate_ellipsoid(cJSON *tmp[], t_figure *figure);
char			*validate_paraboloid(cJSON *tmp[], t_figure *figure);
char			*validate_limited_cylinder(cJSON *tmp[], t_figure *figure);
char			*validate_limited_cone(cJSON *tmp[], t_figure *figure);
char			*validate_limited_paraboloid(cJSON *tmp[], t_figure *figure);
char			*validate_limited_sphere(cJSON *tmp[], t_figure *figure);
char			*validate_object_texture(cJSON *obj, t_figure *figure);
char			*validate_texture(cJSON *obj, t_figure *figure);
char			*validate_perlin(cJSON *obj, t_figure *figure);
char			*validate_plasma(cJSON *obj, t_figure *figure);
char			*validate_contours(cJSON *obj, t_figure *figure);
char			*validate_caustic(cJSON *obj, t_figure *figure);
char			*validate_jupiter(cJSON *obj, t_figure *figure);
_Bool			validate_vector(cJSON *obj, t_vect *vect);
_Bool			validate_color(cJSON *obj, t_color *color);
void			valid_data(char *arr[], char *type);
void			valid_data_2(char *arr[], char *type);
void			valid_id_list(int arr[]);
void			valid_id_list_2(int arr[]);
_Bool			valid_hex(char *str);
_Bool			valid_color(cJSON *obj, t_color *color);
void			json_free(cJSON **tmp, int size);

/*
** loading bar ????
*/
int 			animation(SDL_Renderer *renderer, t_rtv *rtv);
void 			load_texture1(t_rtv *rtv);
void 			load_texture2(t_rtv *rtv);
void 			load_texture3(t_rtv *rtv);

/*
** що виконують ці функції
*/

void create_rander_texture(t_rtv *rtv);
int randon(int low, int hight);
unsigned int rand_interval(unsigned int min, unsigned int max);

/*
** key hooks
*/
void			key_funct_7(t_rtv *rtv);
void			key_funct_6(t_rtv *rtv);
void			key_funct_5(t_rtv *rtv);
void			key_funct_4(t_rtv *rtv);
void			key_funct_3(t_rtv *rtv);
void			key_funct_2(t_rtv *rtv);
void			key_funct_1(t_rtv *rtv);
int				my_key_funct(t_rtv *rtv);

/*
** functions for SDL
*/
void			ft_redraw(t_rtv *rtv);
void			ft_take_picture(t_rtv *rtv);
void			ft_menu(t_menu *menu, t_rtv *rtv);
void			ft_which_scene(t_rtv *rtv, int i);
char			*ft_itoa(int n);
double	check_sphere_limits(double t, t_ray *r, t_limited_sphere *c);
void	delstruct1(t_menu *menu);

#endif
