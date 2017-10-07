/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightening_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 21:16:32 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/02 16:30:10 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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

void	directional_light_ray(t_light *l, t_additional *st)
{
	st->light_ray.dir = l->direction;
	st->rev_light_ray.dir = change_vector_direction(&l->direction);
	st->light_ray.origin = st->point;
	st->rev_light_ray.origin = st->point;
	st->len = INFINITY;
	st->spot_coef = 1.0;
}

void	point_light_ray(t_light *l, t_additional *st)
{
	st->light_ray.dir = vector_substract(&st->point, &l->pos);
	st->len = vector_length(&st->light_ray.dir);
	st->light_ray.dir = normalize_vector(&st->light_ray.dir);
	st->rev_light_ray.dir = change_vector_direction(&st->light_ray.dir);
	st->light_ray.origin = st->point;
	st->rev_light_ray.origin = st->point;
	st->spot_coef = 1.0;
}

static void	spot_light_ray(t_light *l, t_additional *st)
{
	double theta;

	st->light_ray.dir = vector_substract(&st->point, &l->pos);
	st->len = vector_length(&st->light_ray.dir);
	st->light_ray.dir = normalize_vector(&st->light_ray.dir);
	st->rev_light_ray.dir = change_vector_direction(&st->light_ray.dir);
	st->light_ray.origin = st->point;
	st->rev_light_ray.origin = st->point;
	theta = vector_dot_product(&st->light_ray.dir, &l->direction);
	st->spot_coef = (theta - l->outer_cone) / l->epsilon;
	if (st->spot_coef < PRECISION)
		st->spot_coef = 0;
	if (st->spot_coef > 1)
		st->spot_coef = 1;
}

void		create_light_ray(t_light *l, t_additional *st)
{
	if (l->type == DIRECTIONAL_LIGHT)
		directional_light_ray(l, st);
	else if (l->type == POINT_LIGHT)
		point_light_ray(l, st);
	else if (l->type == SPOT_LIGHT)
		spot_light_ray(l, st);
}
