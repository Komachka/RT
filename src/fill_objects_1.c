/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 02:22:21 by kzahreba          #+#    #+#             */
/*   Updated: 2017/06/08 21:10:13 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 	fill_triangle(t_figure *f, t_vect a, t_vect b, t_vect c)
{
	t_triangle *tr;
	t_vect tm1;
	t_vect tm2;

	f->id = TRIANGLE;
	if (!(f->object = (t_triangle *)malloc(sizeof(t_triangle))))
		malloc_error();
	tr = (t_triangle *)f->object;
	tr->a = a;
	tr->b = b;
	tr->c = c;
	tm1 = vector_substract(&b, &a);
	tm2 = vector_substract(&c, &a);
	tr->norm = vector_cross_product(&a, &b);
	tr->norm = normalize_vector(&tr->norm);
	tr->edge_ba = tm1;
	tr->edge_cb = vector_substract(&c, &b);
	tr->edge_ac = vector_substract(&a, &c);
	f->intersection_object = &intersection_triangle;
	f->norm_vector = &triangle_norm_vector;
}

void	fill_sphere(t_figure *f, t_vect pos, double rd)
{
	t_sphere *s;

	f->id = SPHERE;
	if (!(f->object = (t_sphere *)malloc(sizeof(t_sphere))))
		malloc_error();
	s = (t_sphere *)f->object;
	s->pos = pos;
	s->r = rd;
	f->intersection_object = &intersection_sphere;
	f->norm_vector = &sphere_norm_vector;
}

void	fill_cone(t_figure *f, t_vect p, t_vect d, double angle)
{
	t_cone *cn;

	f->id = CONE;
	if (!(f->object = (t_cone *)malloc(sizeof(t_cone))))
		malloc_error();
	cn = (t_cone *)f->object;
	cn->pos = p;
	cn->dir = normalize_vector(&d);
	cn->rad = degrees_to_radians(angle);
	f->intersection_object = &intersection_cone;
	f->norm_vector = &cone_norm_vector;
}

void	fill_plane(t_figure *f, t_vect pt, t_vect n)
{
	t_plane *p;

	f->id = PLANE;
	if (!(f->object = (t_plane *)malloc(sizeof(t_plane))))
		malloc_error();
	p = (t_plane *)f->object;
	p->norm = normalize_vector(&n);
	p->point = pt;
	f->intersection_object = &intersection_plane;
	f->norm_vector = &plane_norm_vector;
}

void	fill_cylinder(t_figure *f, t_vect p, t_vect d, double rd)
{
	t_cylinder	*c;

	f->id = CYLINDER;
	if (!(f->object = (t_cylinder *)malloc(sizeof(t_cylinder))))
		malloc_error();
	c = (t_cylinder *)f->object;
	c->pos = p;
	c->dir = normalize_vector(&d);
	c->r = rd;
	f->intersection_object = &intersection_cylinder;
	f->norm_vector = &cylinder_norm_vector;
}

void	fill_torus(t_figure *f, t_vect p, t_vect d, double min_r, double maj_r)
{
	t_torus *t;

	f->id = TORUS;
	if (!(f->object = (t_torus *)malloc(sizeof(t_torus))))
		malloc_error();
	t = (t_torus *)f->object;
	t->pos = p;
	t->dir = normalize_vector(&d);
	t->min_r = min_r;
	t->maj_r = maj_r;
	f->intersection_object = &intersection_torus;
	f->norm_vector = &torus_norm_vector;
}