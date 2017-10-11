/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:36:10 by askochul          #+#    #+#             */
/*   Updated: 2017/10/11 15:58:48 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect		disc_with_hole_norm_vector(void *obj, t_vect *point)
{
	t_vect				norm;
	t_disc_with_hole	*p;

	p = (t_disc_with_hole *)obj;
	if (vector_dot_product(&p->disc.norm, point) > PRECISION)
		norm = change_vector_direction(&p->disc.norm);
	else
		norm = p->disc.norm;
	return (norm);
}
