/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_phong_model_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 21:13:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/16 21:13:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

#define COS_I 0
#define ETAI 1
#define ETAT 2
#define ETA 3
#define K 4

static inline t_vect	refracted_vector(t_vect *norm, t_vect *incident,
														double refract_coef)
{
	t_vect	n;
	t_vect	refr;
	t_vect	tmp[2];
	double	dbl[5];

	dbl[ETAI] = 1;
	dbl[ETAT] = refract_coef;
	n = *norm;
	dbl[COS_I] = vector_dot_product(incident, norm);
	if (dbl[COS_I] < 0)
		dbl[COS_I] *= -1;
	else
	{
		dbl[ETAI] = refract_coef;
		dbl[ETAT] = 1;
		n = change_vector_direction(&n);
	}
	dbl[ETA] = dbl[ETAI] / dbl[ETAT];
	dbl[K] = 1.0 - dbl[ETA] * dbl[ETA] * (1.0 - dbl[COS_I] * dbl[COS_I]);
	if (dbl[K] < 0)
		return (create_vector(0, 0, 0));
	tmp[0] = vector_mult(dbl[ETA], incident);
	tmp[1] = vector_mult(dbl[ETA] * dbl[COS_I] - sqrt(dbl[K]), &n);
	refr = vector_add(&tmp[0], &tmp[1]);
	return (normalize_vector(&refr));
}

t_color					refractive_component(t_additional *st, t_rtv *rtv,
														int recursive_depth)
{
	t_vect	t;
	t_color	res;
	t_ray	r;

	r.dir = refracted_vector(&st->norm, &st->primary_ray.dir,
														st->mat.refraction);
	r.origin = st->point;
	r.origin = adding_bias(&st->point, &r.dir);
	t.z = INFINITY;
	set_zero_color(&res);
	if ((complicated_intersection(rtv, &r, &t)) != -1)
	{
		res = colorizing(rtv, t, &r, recursive_depth + 1);
		res = calculate_color(st->mat.transparency, &res);
	}
	else
		res = create_background_color(rtv, &r);
	return (res);
}

static inline void		diffuse_component(t_light *l, t_additional *st,
											t_final_color *c)
{
	double	diff;

	if (st->mat.transparency > PRECISION)
		set_zero_color(&c->d);
	else
	{
		diff = st->spot_coef * vector_dot_product(&st->norm,
													&st->rev_light_ray.dir);
		if (diff < PRECISION)
			diff = 0;
		st->diff += diff;
		c->d = mult_color_coefs(calculate_color(diff, &l->intensity),
								st->mat.cl);
		c->d = mult_color_coefs(c->d, st->mat.diffuse);
		c->d = calculate_color(st->attenuation, &c->d);
	}
}

static inline void		specular_component(t_light *l, t_additional *st,
												t_vect *cam, t_final_color *c)
{
	double	spec;
	t_vect	refl;
	t_vect	v;

	spec = 0;
	if (st->mat.shininess > PRECISION)
	{
		refl = reflected_vector(&st->light_ray.dir, &st->norm);
		v = vector_substract(cam, &st->point);
		v = normalize_vector(&v);
		spec = vector_dot_product(&v, &refl);
		if (spec < PRECISION)
			spec = 0;
		spec = st->spot_coef * pow(spec, st->mat.shininess);
	}
	c->s = calculate_color(spec * st->attenuation, &st->mat.specular);
	c->s = mult_color_coefs(c->s, l->intensity);
}

void					lambert_2(t_rtv *rtv, t_additional *s,
												t_final_color *lights, int k)
{
	create_light_ray(&rtv->l[k], s);
	s->attenuation = rtv->l[k].k_const == 0 && rtv->l[k].k_linear == 0 &&
			rtv->l[k].k_quadratic == 0 ? 1 :
			min(1.00 / (rtv->l[k].k_const + rtv->l[k].k_linear * s->len +
					rtv->l[k].k_quadratic * pow(s->len, 2)), 1);
	if (!shadow(rtv, &s->rev_light_ray, s->len))
	{
		diffuse_component(&rtv->l[k], s, &lights[k]);
		specular_component(&rtv->l[k], s, &rtv->cam.pos, &lights[k]);
	}
	else
	{
		set_zero_color(&lights[k].d);
		set_zero_color(&lights[k].s);
	}
}
