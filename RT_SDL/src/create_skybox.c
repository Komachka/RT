
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 21:53:41 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/09 21:53:48 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	skybox_mapping_texture(t_skybox *skybox, t_vect *point, t_color *col)
{
	t_vect				temp;
	t_mapping_texture	*tx;
	double				u[2];
	int					x[2];

	tx = (t_mapping_texture *)skybox->texture.tx_struct;
	temp = vector_substract(point, &skybox->pos);
	temp = normalize_vector(&temp);
	u[0] = 0.5 + (atan2(temp.z, temp.x) / (2.0 * M_PI));
	u[1] = 0.5 - (asin(temp.y) / M_PI);
	x[0] = (u[0] * tx->w);
	x[1] = (u[1] * tx->h);
	*col = parse_color(tx->arr[x[0] + tx->w * x[1]]);
}

t_color	creating_skybox(t_rtv *rtv, t_ray *rd)
{
	t_equation		n;
	t_vect			dist;
	t_additional	s;
	t_ray			r;

	r.origin = rtv->skybox.pos;
	r.dir = rd->dir;
	n.a = vector_dot_product(&r.dir, &r.dir);
	dist = vector_substract(&r.origin, &rtv->skybox.pos);
	n.b = 2.0 * vector_dot_product(&dist, &r.dir);
	n.c = vector_dot_product(&dist, &dist) - (rtv->skybox.r * rtv->skybox.r);
	s.point = intersection_point(select_value(n.root, \
		quadratic_equation(&n)), &r);
	s.mat.cl = rtv->skybox.cl;
	if (rtv->skybox.texturing == ON)
	{
		if (rtv->skybox.texture.type == MAPPING)
			skybox_mapping_texture(&rtv->skybox, &s.point, &s.mat.cl);
		else
			rtv->skybox.texture.creating_texture(&s, \
				rtv->skybox.texture.tx_struct);
		return (s.mat.cl);
	}
	else
		return (rtv->skybox.cl);
}