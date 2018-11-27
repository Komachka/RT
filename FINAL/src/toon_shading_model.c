/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toon_shading_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 21:06:44 by kzahreba          #+#    #+#             */
/*   Updated: 2017/07/23 21:06:59 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_color		toon_shading_model(t_rtv *rtv, t_additional *s)
{
	int		k;
	double	diff;
	t_color	lights[rtv->light_num];

	k = -1;
	while (++k < rtv->light_num)
	{
		create_light_ray(&rtv->l[k], s);
		if (!shadow(rtv, &s->rev_light_ray, s->len))
		{
			diff = s->spot_coef * vector_dot_product(&s->norm, \
				&s->rev_light_ray.dir);
			if (diff > 0.95)
				lights[k] = calculate_color(1, &s->mat.cl);
			else if (diff > 0.5)
				lights[k] = calculate_color(0.7, &s->mat.cl);
			else if (diff > 0.05)
				lights[k] = calculate_color(0.35, &s->mat.cl);
			else
				lights[k] = calculate_color(0.2, &s->mat.cl);
		}
		else
			lights[k] = calculate_color(0.1, &s->mat.cl);
	}
	return (average_color(lights, rtv->light_num));
}
