/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_phong_model_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 20:25:50 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 22:46:20 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect					reflected_vector(t_vect *v, t_vect *norm)
{
	double	tm;
	t_vect	refl;

	tm = 2 * vector_dot_product(norm, v);
	refl = vector_mult(tm, norm);
	refl = vector_substract(v, &refl);
	refl = normalize_vector(&refl);
	return (refl);
}

static inline t_color	reflection_component(t_additional *st, t_rtv *rtv,
											int recursive_depth, double coef)
{
	t_vect	t;
	t_vect	tmp;
	t_color	res;
	t_ray	r;

	tmp = st->primary_ray.dir;
	r.dir = reflected_vector(&tmp, &st->norm);
	r.origin = adding_bias(&st->point, &r.dir);
	t.z = INFINITY;
	set_zero_color(&res);
	if ((complicated_intersection(rtv, &r, &t)) != -1)
	{
		res = colorizing(rtv, t, &r, recursive_depth + 1);
		res = calculate_color(coef, &res);
	}
	else
		res = create_background_color(rtv, &r);
	return (res);
}

static inline t_color	super_final_color(t_additional *s, t_color total_diff,
										t_color total_spec, double sum)
{
	t_color	res;

	if (s->mat.reflective > PRECISION || s->mat.transparency > PRECISION)
	{
		total_diff = calculate_color(1.0 - sum, &total_diff);
		s->a = calculate_color(1.0 - sum, &s->a);
	}
	res.r = min(s->a.r + s->r.r + s->refr.r + total_diff.r + total_spec.r, 1);
	res.g = min(s->a.g + s->r.g + s->refr.g + total_diff.g + total_spec.g, 1);
	res.b = min(s->a.b + s->r.b + s->refr.b + total_diff.b + total_spec.b, 1);
	res.al = min(s->a.al + total_diff.al + total_spec.al, 1);
	return (res);
}

static inline t_color	final_color(t_final_color *lights, t_rtv *rtv,
															t_additional *s)
{
	t_color	total_diff;
	t_color	total_spec;
	int		i;
	double	sum;

	i = -1;
	set_zero_color(&total_diff);
	set_zero_color(&total_spec);
	sum = s->mat.reflective + s->mat.transparency;
	if (sum > 1.0f)
		sum = 1.0;
	while (++i < rtv->light_num)
	{
		total_diff.r += lights[i].d.r;
		total_diff.g += lights[i].d.g;
		total_diff.b += lights[i].d.b;
		total_diff.al += lights[i].d.al;
		total_spec.r += lights[i].s.r;
		total_spec.g += lights[i].s.g;
		total_spec.b += lights[i].s.b;
		total_spec.al += lights[i].s.al;
	}
	free(lights);
	return (super_final_color(s, total_diff, total_spec, sum));
}

t_color					lambert_phong_model(t_rtv *rtv, t_additional *s,
													int recursive_depth)
{
	int				k;
	t_final_color	*lights;

	lights = (t_final_color*)malloc(sizeof(t_final_color) * rtv->light_num);
	k = -1;
	set_zero_color(&s->r);
	set_zero_color(&s->refr);
	if (s->mat.transparency > PRECISION)
		set_zero_color(&s->a);
	else
		s->a = mult_color_coefs(mult_color_coefs(s->mat.ambient,
												rtv->global_light), s->mat.cl);
	while (++k < rtv->light_num)
		lambert_2(rtv, s, lights, k);
	if (recursive_depth < rtv->recursive_depth)
	{
		if (s->mat.reflective > PRECISION)
			s->r = reflection_component(s, rtv, recursive_depth,
					s->mat.reflective);
		if (s->mat.transparency > PRECISION)
			s->refr = refractive_component(s, rtv, recursive_depth);
	}
	return (final_color(lights, rtv, s));
}
