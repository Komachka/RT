/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightening_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 21:16:32 by kzahreba          #+#    #+#             */
/*   Updated: 2017/07/04 21:16:37 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			shadow(t_rtv *rtv, t_ray *r, double light)
{
	int		i;
	int		k;
	double	t;

	i = -1;
	k = 0;
	while (++i < rtv->figure_num)
		if (rtv->objects[i].intersection_object(r, rtv->objects[i].object, &t))
		{
			if (t > light)
				continue;
			else
			{
				k = 1;
				break ;
			}
		}
	return (k);
}

double		diffuse_light(t_light *l, t_vect *norm, t_vect *point)
{
	t_vect lt;
	double dot;

	lt = vector_substract(&l->pos, point);
	lt = normalize_vector(&lt);
	dot = vector_dot_product(norm, &lt);
	if (dot < 0.0001f)
		dot = 0;
	return (dot);
}

double		specular_light(t_light *l, t_vect *norm, t_vect *point, t_vect *cam)
{
	t_vect lt;
	t_vect refl;
	double dot;
	t_vect v;

	lt = vector_substract(&l->pos, point);
	lt = normalize_vector(&lt);
	refl = reflected_vector(&lt, norm);
	v = normalize_vector(cam);
	dot = vector_dot_product(&v, &refl);
	if (dot < 0.0001f)
		dot = 0;
	return (dot);
}
