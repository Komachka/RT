/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_projection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 18:34:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 18:34:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline t_vect	rotate_cam(t_vect *dir, double *angles)
{
	t_vect	res;
	t_vect	tmp;

	res.x = dir->x;
	res.y = dir->y * cos(angles[X]) + dir->z * sin(angles[X]);
	res.z = -1 * dir->y * sin(angles[X]) + dir->z * cos(angles[X]);
	tmp.y = res.y;
	tmp.x = res.x * cos(angles[Y]) + res.z * sin(angles[Y]);
	tmp.z = -1 * res.x * sin(angles[Y]) + res.z * cos(angles[Y]);
	res.z = tmp.z;
	res.x = tmp.x * cos(angles[Z]) + tmp.y * sin(angles[Z]);
	res.y = -1 * tmp.x * sin(angles[Z]) + tmp.y * cos(angles[Z]);
	return (res);
}

static inline t_vect	fisheye_camera(t_vect *dir, double angle)
{
	double	r;
	double	phi;
	double	theta;
	t_vect	res;

	phi = 0;
	r = sqrt(dir->x * dir->x + dir->y * dir->y);
	if (r == 0.00f)
		phi = 0;
	else if (dir->x < 0.00f)
		phi = M_PI - asin(dir->y / r);
	else if (dir->x >= 0.00f)
		phi = asin(dir->y / r);
	theta = r * TO_RAD(angle);
	res.x = sin(theta) * cos(phi);
	res.y = sin(theta) * sin(phi);
	res.z = cos(theta);
	return (res);
}

void					calculations_for_make_projection(t_thred *p,
											t_vect *tmp, t_color *c, int *i)
{
	t_vect	tm;
	int		figure;

	p->ray.dir = rotate_cam(tmp, p->rtv1->cam.rotate);
	if (p->rtv1->cam.type == FISHEYE)
		p->ray.dir = fisheye_camera(&p->ray.dir, p->rtv1->cam.fisheye_angle);
	p->ray.dir = normalize_vector(&p->ray.dir);
	tm.z = INFINITY;
	figure = complicated_intersection(p->rtv1, &p->ray, &tm);
	set_zero_color(&c[(*i)]);
	if (figure != -1)
		c[(*i)] = p->rtv1->lightening == ON ?
				colorizing(p->rtv1, tm, &p->ray, 0) :
				p->rtv1->objects[figure].material.cl;
	else
		c[(*i)] = create_background_color(p->rtv1, &p->ray);
	(*i)++;
}
