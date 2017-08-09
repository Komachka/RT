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
