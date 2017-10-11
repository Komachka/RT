/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:51:17 by askochul          #+#    #+#             */
/*   Updated: 2017/10/11 17:55:49 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	sphere_mapping_texture(t_additional *s, void *t)
{
	t_rtv				*rtv;
	t_mapping_texture	*tx;
	double				u;
	double				v;
	int					x0;
	int					x1;
	t_sphere			*sp;
	t_vect				temp;

	rtv = (t_rtv *)t;
	u = 0;
	v = 0;
	sp = (t_sphere*)rtv->objects[s->figure].object;
	tx = (t_mapping_texture *)rtv->objects[s->figure].texture.tx_struct;
	temp = vector_substract(&s->point, &sp->pos);
	temp = normalize_vector(&temp);
	u = 0.5 + (atan2(temp.z, temp.x) / (2.0 * M_PI));
	v = 0.5 - (asin(temp.y) / M_PI);
	x0 = (u * tx->w);
	x1 = (v * tx->h);
	s->mat.cl = parse_color(tx->arr[x0 + tx->w * x1]);
}
