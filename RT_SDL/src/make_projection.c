/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:24:07 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/15 13:30:41 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline t_vect	rotate_x(t_vect *dir, double rx)
{
	t_vect	res;

	res.x = dir->x;
	res.y = dir->y * cos(rx) + dir->z * sin(rx);
	res.z = -1 * dir->y * sin(rx) + dir->z * cos(rx);
	return (res);
}

static inline t_vect	rotate_y(t_vect *dir, double ry)
{
	t_vect	res;

	res.y = dir->y;
	res.x = dir->x * cos(ry) + dir->z * sin(ry);
	res.z = -1 * dir->x * sin(ry) + dir->z * cos(ry);
	return (res);
}

static inline t_vect	rotate_z(t_vect *dir, double rz)
{
	t_vect	res;

	res.z = dir->z;
	res.x = dir->x * cos(rz) + dir->y * sin(rz);
	res.y = -1 * dir->x * sin(rz) + dir->y * cos(rz);
	return (res);
}

static inline t_vect	rotate_cam(t_vect dir, double *angles)
{
	t_vect	res;
	t_vect	tmp;

	res = rotate_x(&dir, angles[X]);
	tmp = rotate_y(&res, angles[Y]);
	res = rotate_z(&tmp, angles[Z]);
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

void					*make_projection(void *k)
{
	t_thred	*p;
	t_color	*c;
	int		i;
	int		x;
	t_vect	tmp;
	int		dx;
	int		dy;
	t_color	average;

	dx = -1;
	dy = -1;
	p = (t_thred *)k;
	tmp.z = p->rtv1->cam.lk_dir;
	c = (t_color*)malloc(sizeof(t_color) * p->rtv1->samples);
	i = 0;
	while (p->y_start < p->y_end)
	{
		x = -1;
		p->ray.origin = p->rtv1->cam.pos;
		{
			while (++x < WX)
			{
				while (++dx < p->rtv1->samples)
				{
					while (++dy < p->rtv1->samples)
					{
						tmp.x = (2 * ((x + p->rtv1->delta_aliasing + (double)dx /
										(double)p->rtv1->samples) / (double)WX) - 1) *
							p->rtv1->cam.image_aspect_ratio * p->rtv1->cam.scale;
						tmp.y = (1 - 2 * ((p->y_start + p->rtv1->delta_aliasing + (double)dy / (double)p->rtv1->samples) / (double)WY)) * p->rtv1->cam.scale;
						p->ray.dir = rotate_cam(tmp, p->rtv1->cam.rotate);
						if (p->rtv1->cam.type == FISHEYE)
							p->ray.dir = fisheye_camera(&p->ray.dir, p->rtv1->cam.fisheye_angle);
						p->ray.dir = normalize_vector(&p->ray.dir);
						c[i++] = intersection(p->rtv1, &p->ray);
					}
					dy = -1;
				}
				dx = -1;
				average = average_color(c, p->rtv1->samples); 
				correct_exposure(p->rtv1, &average);
				paint_image(p->rtv1, x, p->y_start, average);
				i = 0;
			}
		}
		if (p->index == 0 && p->rtv1->delphin == ON)
			animation(p->rtv1->renderer, p->rtv1);
		p->y_start++;
	}
	free(c);
	return (0);
}
