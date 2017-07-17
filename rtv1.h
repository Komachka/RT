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
# define X 0
# define Y 1
# define Z 2
# include <mlx.h>
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
	t_vect		pos;
	double		rotate[3];
	double		fov_h;
	double		image_aspect_ratio;
	double		scale;
}				t_camera;

typedef	struct	s_color
{
	double		b;
	double		g;
	double		r;
	double		al;
}				t_color;

typedef struct	s_light
{
	t_vect		pos;
	t_color		cl;
}				t_light;

typedef	struct	s_material
{
	t_color		cl;
	double		ambient_strength;
	double		specular_strength;
	double		diffuse_strength;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	int			shininess;
}				t_material;

typedef struct	s_ray
{
	t_vect		start;
	t_vect		dir;
}				t_ray;

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

typedef struct	s_figure
{
	int			id;
	void		*object;
	int			(*intersection_object)(t_ray *, void *, double *);
	t_vect		(*norm_vector)(void *, t_vect *);
	t_material	material;
}				t_figure;

typedef struct	s_rtv
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pic;
	int			len;
	int			light_num;
	int			lightening;
	int			figure_num;
	t_camera	cam;
	t_light		*l;
	int			cam_distance;
	t_figure	*objects;
	int			shift_x;
	int			shift_y;
	int			shift_z;
	double		angles[3];
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

typedef struct	s_additional
{
	t_vect		point;
	t_vect		norm;
	t_ray		rayl;
	t_material	mat;
	double		diff;
	double		spec;
	int			shad;
	double		len;
}				t_additional;

/*
** actions with vectors
*/
double			vector_dot_product(t_vect *v1, t_vect *v2);
t_vect			vector_add(t_vect *v1, t_vect *v2);
t_vect			vector_substract(t_vect *v1, t_vect *v2);
t_vect			vector_mult(double i, t_vect *v1);
double			vector_length(t_vect *v);
t_vect			normalize_vector(t_vect *v1);
void			vector_rewrite(t_vect *v1, t_vect *v2);
t_vect			reflected_vector(t_vect *v, t_vect *norm);
t_vect			change_vector_direction(t_vect *v);
t_vect			create_vector(double x, double y, double z);

/*
** filling object's parameters
*/
void			fill_sphere(t_figure *f, t_vect pos, double rd);
void			fill_cone(t_figure *f, t_vect pos, t_vect dir, double angle);
void			fill_plane(t_figure *f, t_vect point, t_vect norm);
void			fill_cylinder(t_figure *f, t_vect p, t_vect d, double rd);
void			fill_light(t_light *l, t_vect pos, char *color);
void			set_camera(t_camera *cam, t_vect pos, t_vect dir, double angle);
void			set_material(t_figure *f, t_vect ads, int sh, char *cl);
t_color			create_color(char *hex);

/*
** intersection functions for objects
*/
int				intersection_sphere(t_ray *r, void *sphere, double *t);
int				intersection_cone(t_ray *r, void *cone, double *t);
int				intersection_plane(t_ray *r, void *plane, double *t);
int				intersection_cylinder(t_ray *r, void *cylinder, double *t);
void			intersection(t_rtv *rtv, t_ray *r, int x, int y);
t_vect			intersection_point(double t, t_ray *r);

/*
** calculating norm vectors for objects
*/
t_vect			sphere_norm_vector(void *obj, t_vect *point);
t_vect			plane_norm_vector(void *obj, t_vect *point);
t_vect			cylinder_norm_vector(void *obj, t_vect *point);
t_vect			cone_norm_vector(void *obj, t_vect *point);
t_vect			find_norm(t_rtv *rtv, int figure, t_vect *point, t_vect *r_dir);

/*
** colorizing
*/
t_color			calculate_color(double i, t_color *c);
t_color			average_color(t_color *lights, t_rtv *rtv);
void			paint_image(t_rtv *r, int x, int y, t_color *cl);
t_color			colorizing(t_rtv *rtv, int figure, double t, t_ray *r);

/*
**  actions with light
*/
double			diffuse_light(t_light *l, t_vect *norm, t_vect	*point);
double			specular_light(t_light *l, t_vect *n, t_vect *p, t_vect *rtv);
int				shadow(t_rtv *rtv, t_ray *r, double light);
void			calculate_light(t_material *c, t_color *light, int shad);

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
void			calculate_screen(t_rtv *rtv);
int				end_function(void);
void			new_image(t_rtv *rtv);
void			delstruct(t_rtv *rtv);
int				ft_atoi_base(const char *str, int base);
size_t			ft_strlen(char const *str);
void			ft_putendl(char const *s);
void			scene_1(t_rtv *rtv);
void			scene_2(t_rtv *rtv);
void			scene_3(t_rtv *rtv);
void			scene_4(t_rtv *rtv);
void			scene_5(t_rtv *rtv);

#endif
