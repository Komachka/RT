/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:06:25 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 22:19:24 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect	change_vector_direction(t_vect *v)
{
	t_vect new;

	new.x = -v->x;
	new.y = -v->y;
	new.z = -v->z;
	return (new);
}

t_vect	create_vector(double x, double y, double z)
{
	t_vect v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	vector_length(t_vect *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

t_vect	project_point_on_plane(t_vect *point, t_vect *pl_point, t_vect *pl_norm)
{
	t_vect v;

	v = vector_substract(pl_point, point);
	v = vector_mult(vector_dot_product(&v, pl_norm), pl_norm);
	return (vector_add(point, &v));
}

t_vect	mult_vectors_coordinates(t_vect *v1, t_vect *v2)
{
	return (create_vector(v1->x * v2->x, v1->y * v2->y, v1->z * v2->z));
}
