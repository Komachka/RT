/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 18:32:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 18:32:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	calculations(t_thred *p, t_vect *tmp, t_color *c, int x)
{
	t_color	average;
	int		dy;
	int		dx;
	int		i;

	i = 0;
	dx = 0;
	while (dx < p->rtv1->grid)
	{
		dy = 0;
		while (dy < p->rtv1->grid)
		{
			tmp->x = (2 * ((x + p->rtv1->delta_aliasing + dx /
					p->rtv1->samples) / WX) - 1) *
					p->rtv1->cam.image_aspect_ratio * p->rtv1->cam.scale;
			tmp->y = (1 - 2 * ((p->y_start + p->rtv1->delta_aliasing + dy /
					p->rtv1->samples) / WY)) * p->rtv1->cam.scale;
			calculations_for_make_projection(p, tmp, c, &i);
			dy++;
		}
		dx++;
	}
	average = average_color(c, p->rtv1->samples);
	correct_exposure(p->rtv1, &average);
	paint_image(p->rtv1, x, p->y_start, average);
}

void				*make_projection(void *k)
{
	t_thred	*p;
	t_color	*c;
	t_vect	tmp;
	int		x;

	p = (t_thred *)k;
	tmp.z = p->rtv1->cam.lk_dir;
	c = (t_color*)malloc(sizeof(t_color) * p->rtv1->samples);
	while (p->y_start < p->y_end)
	{
		x = 0;
		p->ray.origin = p->rtv1->cam.pos;
		while (x < WX)
		{
			calculations(p, &tmp, c, x);
			x++;
		}
		if (p->index == 0 && p->rtv1->delphin == ON)
			animation(p->rtv1);
		p->y_start++;
	}
	free(c);
	return (0);
}
