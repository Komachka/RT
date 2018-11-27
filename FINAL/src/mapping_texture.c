/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:51:17 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 21:29:37 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	sphere_mapping_texture(t_additional *s, void *t)
{
	t_rtv				*rtv;
	t_mapping_texture	*tx;
	t_sphere			*sp;
	t_vect				temp;

	rtv = (t_rtv *)t;
	sp = (t_sphere*)rtv->objects[s->figure].object;
	tx = (t_mapping_texture *)rtv->objects[s->figure].texture.tx_struct;
	temp = vector_substract(&s->point, &sp->pos);
	temp = normalize_vector(&temp);
	VAR_INT(i, 0);
	i = (int)((0.5 + (atan2(temp.z, temp.x) / (2.0 * M_PI))) * tx->w) + tx->w *
			(int)((0.5 - (asin(temp.y) / M_PI)) * tx->h);
	s->mat.cl = parse_color(tx->arr[i]);
}
