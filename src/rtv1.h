/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 20:36:45 by kzahreba          #+#    #+#             */
/*   Updated: 2017/04/04 20:40:48 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WX 1000
# define WY 1000

# define NUM_THREADS 4
# define BIAS 0.001

# define X 0
# define Y 1
# define Z 2

# define ON 1
# define OFF 0

/*
** lightening types
*/
# define LAMBERT 1
# define CARTOON 2

/*
** camera  types
*/

# define STANDART 0
# define FISHEYE 1


/*
** figure types
*/
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define TORUS 5
# define TRIANGLE 6

/*
** light types
*/
# define DIRECTIONAL_LIGHT 1
# define POINT_LIGHT 2
# define SPOT_LIGHT 3

/*
**	key hooks
*/

# define SPACE 49
# define KEY_B 11
# define KEY_P 35
# define KEY_R 15
# define PLUS 69
# define MINUS 78
# define DOWN 125
# define UP 126
# define RIGHT 124
# define LEFT 123
# define TOP_PLUS 24
# define TOP_MINUS 27
# define TOP_NUM_1 18
# define TOP_NUM_2 19
# define ESC 53


# include "../libraries/minilibx_macos/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

typedef	struct	s_camera
{
	int 		type;
	double 		fisheye_angle;
	t_vect		pos;
	double		rotate[3];
	double		image_aspect_ratio;
	double		scale;
	double		lk_dir;
}				t_camera;

typedef	struct	s_color
{
	double		b;
	double		g;
	double		r;
	double		al;
}				t_color;

typedef	struct	s_material
{
	t_color		cl;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double 		refraction; // refractive index
	int 		texture;
}				t_material;

typedef struct	s_ray
{
	t_vect		origin;
	t_vect		dir;
}				t_ray;

typedef struct	s_additional
{
	int 		figure;
	t_vect		point;
	t_vect		norm;
	t_ray		light_ray;
	t_ray		rev_light_ray;
	t_ray		primary_ray;
	t_material	mat;
	double 		attenuation;
	t_color		a;
	t_color		d;
	t_color		s;
	t_color 	r;
	t_color 	refr;
	double		diff;
	double		len;
	double		spot_coef;
}				t_additional;


typedef struct	s_light
{
	int  		type;
	t_vect		pos;
	t_color		intensity;
	t_vect		direction;
	double		k_const; // coefs for light attenuation
	double		k_linear;
	double 		k_quadratic;
	double		outer_cone;
	double 		inner_cone;
	double		epsilon;
}				t_light;

typedef struct	s_sphere
{
	t_vect		pos;
	double		r;
	t_material	mt;
}				t_sphere;

typedef struct	s_plane
{
	t_vect		norm;
	t_vect		point;
	t_material	mt;
}				t_plane;

typedef struct	s_cylinder
{
	t_vect		pos;
	t_vect		dir;
	double		r;
	t_material	mt;
}				t_cylinder;

typedef struct	s_cone
{
	t_vect		pos;
	t_vect		dir;
	double		rad;
	t_material	mt;
}				t_cone;

typedef struct s_torus
{
	t_vect		pos;	// C
	t_vect		dir;	// A
	double		maj_r;	// R;
	double		min_r;	//r
	t_material	mt;
}				t_torus;

typedef struct s_triangle
{
	t_vect   	a;
	t_vect   	b;
	t_vect   	c;
	t_vect  	v0;
	t_vect  	v1;
	t_vect 		norm;
}				t_triangle;


typedef struct	s_figure
{
	int			id;
	void		*object;
	t_material	material;
	int			(*intersection_object)(t_ray *, void *, double *);
	t_vect		(*norm_vector)(void *, t_vect *);
}				t_figure;

typedef struct	s_rtv
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pic;
	int			len;
	int			light_num;
	int			figure_num;
	int			lightening;
	int 		light_model;
	int 		recursive_depth;
	int 		bg_color;

	int			samples_grid;
	int 		samples_per_pixel;
	double		delta_aliasing;

	double		air_coef;
	
	t_color 	background_color;
	t_camera	cam;
	t_light		*l;
	t_light		global_light;
	t_figure	*objects;
}				t_rtv;

typedef struct	s_thred
{
	t_rtv		*rtv1;
	int			y;
	t_ray		ray;
}				t_thred;

typedef struct	s_equation
{
	double		a;
	double		b;
	double		c;
	double		t0;
	double		t1;
	double		discr;
	double		sqdiscr;
}				t_equation;

typedef struct  s_final_color
{
	t_color		a;
	t_color		d;
	t_color		s;
}				t_final_color;

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
t_vect			refracted_vector(t_vect *norm, t_vect *incident, double n1, double n2);
t_vect			change_vector_direction(t_vect *v);
t_vect			create_vector(double x, double y, double z);
void 			set_zero_vect(t_vect *v);

/*
** filling object's parameters
*/
void			fill_sphere(t_figure *f, t_vect pos, double rd);
void			fill_cone(t_figure *f, t_vect pos, t_vect dir, double angle);
void			fill_plane(t_figure *f, t_vect point, t_vect norm);
void			fill_cylinder(t_figure *f, t_vect p, t_vect d, double rd);
void			fill_torus(t_figure *f, t_vect p, t_vect d, double min_r, double maj_r);
void 			fill_triangle(t_figure *f, t_vect a, t_vect b, t_vect c);
void 			fill_light(t_light *l, int type, t_vect pos, t_color intensity, t_vect attenuation, t_vect direction, double angle, double outer_cut);
void			set_camera(t_camera *cam, t_vect p, t_vect angle, int type, double fv, double looking_dir, double fy_andle);
void			set_material(t_figure *f, t_color am, t_color dif, t_color spec, double shine, char *cl, double reflective, double transparency, double refraction);
t_color			create_color(char *hex);

/*
** intersection functions for objects
*/
int				intersection_sphere(t_ray *r, void *sphere, double *t);
int				intersection_cone(t_ray *r, void *cone, double *t);
int				intersection_plane(t_ray *r, void *plane, double *t);
int				intersection_cylinder(t_ray *r, void *cylinder, double *t);
int				intersection_torus(t_ray *r, void *torus, double *t);
int 			intersection_triangle(t_ray *r, void *triangle, double *t);
t_color			intersection(t_rtv *rtv, t_ray *r);
t_vect			intersection_point(double t, t_ray *r);
int				complicated_intersection(t_rtv *rtv, t_ray *r, double *point);

/*
** calculating norm vectors for objects
*/
t_vect			sphere_norm_vector(void *obj, t_vect *point);
t_vect			plane_norm_vector(void *obj, t_vect *point);
t_vect			cylinder_norm_vector(void *obj, t_vect *point);
t_vect			cone_norm_vector(void *obj, t_vect *point);
t_vect			torus_norm_vector(void *obj, t_vect *point);
t_vect 			triangle_norm_vector(void *obj, t_vect *point);
t_vect			find_norm(t_rtv *rtv, int figure, t_vect *point, t_vect *r_dir);

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
** basic functions
*/
void			basic_function(t_rtv *rtv);
void			threads(t_rtv *rtv);
void			*make_projection(void *k);

/*
** auxiliary functions
*/
double			min(double i, double j);
int				quadratic_equation(t_equation *n, double *t);
double			degrees_to_radians(double x);
t_vect			adding_bias(t_vect *point, t_vect *dir);
int				end_function(void);
void			new_image(t_rtv *rtv);
void			delstruct(t_rtv *rtv);
int				ft_atoi_base(const char *str, int base);
size_t			ft_strlen(char const *str);
void			ft_putendl(char const *s);
void			scene_1(t_rtv *rtv);

/*
** managing errors
*/

void			malloc_error(void);

#endif
