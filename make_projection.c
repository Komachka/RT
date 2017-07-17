/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:24:07 by kzahreba          #+#    #+#             */
/*   Updated: 2017/05/29 19:24:32 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_vect	calculate_direction(t_vect *map, t_vect *camera, double *angle)
{
	t_ray	r;
	double	x1;
	double	y1;
	double	z1;

	z1 = -1 * camera->y * sin(angle[0]) + camera->z * cos(angle[0]);
	y1 = camera->y * cos(angle[0]) + camera->z * sin(angle[0]);
	
	x1 = camera->x * cos(angle[1]) + z1 * sin(angle[1]);
	r.start.z = -1 * camera->x * sin(angle[1]) + z1 * cos(angle[1]);
	r.start.x = x1 * cos(angle[2]) + y1 * sin(angle[2]);
	r.start.y = -1 * x1 * sin(angle[2]) + y1 * cos(angle[2]);
	z1 = -1 * map->y * sin(angle[0]) + map->z * cos(angle[0]);
	y1 = map->y * cos(angle[0]) + map->z * sin(angle[0]);
	x1 = map->x * cos(angle[1]) + z1 * sin(angle[1]);
	r.dir.z = -1 * map->x * sin(angle[1]) + z1 * cos(angle[1]);
	r.dir.x = x1 * cos(angle[2]) + y1 * sin(angle[2]);
	r.dir.y = -1 * x1 * sin(angle[2]) + y1 * cos(angle[2]);
	r.dir = vector_substract(&r.dir, &r.start);
	r.dir = normalize_vector(&r.dir);
	return (r.start);
}


t_vect	rotate_x(t_vect *dir, double rx)
{
	t_vect res;

	res.x = dir->x;
	res.y = dir->y * cos(rx) + dir->z * sin(rx);
	res.z = -1 * dir->y * sin(rx) + dir->z * cos(rx);
	return (res);
}

t_vect	rotate_y(t_vect *dir, double ry)
{
	t_vect res;

	res.y = dir->y;
	res.x = dir->x * cos(ry) + dir->z * sin(ry);
	res.z = -1 * dir->x * sin(ry) + dir->z * cos(ry);
	return (res);
}

t_vect	rotate_z(t_vect *dir, double rz)
{
	t_vect res;
	
	res.z = dir->z;
	res.x = dir->x * cos(rz) + dir->y * sin(rz);
	res.y = -1 * dir->x * sin(rz) + dir->y * cos(rz);
	return (res);
}

t_vect	rotate_cam(t_vect dir, double *angles)
{
	t_vect res;
	t_vect tmp;

	res = rotate_x(&dir, angles[X]);
	tmp = rotate_y(&res, angles[Y]);
	res = rotate_z(&tmp, angles[Z]);
	return(res);
}
void	*make_projection(void *k)
{
	t_thred	*p;
	int		max;
	int		x;
	t_vect	tmp;

	p = (t_thred *)k;
	max = p->y + WY / 4;
	tmp.z = 1;
	while (p->y < max)
	{
		x = -1;
		p->ray.start = p->rtv1->cam.pos;
		tmp.y = (2 * ((p->y + 0.5) / (double)WY ) - 1) * p->rtv1->cam.scale;
		{
			while (++x < WX)
			{
				tmp.x = (2 * ((x + 0.5) / (double)WX )- 1) * p->rtv1->cam.image_aspect_ratio * p->rtv1->cam.scale;
				tmp = rotate_cam(tmp, p->rtv1->cam.rotate);
				p->ray.dir = normalize_vector(&tmp);
				intersection(p->rtv1, &p->ray, x, p->y);
			}
		}
		p->y++;
	}
	pthread_exit(NULL);
}
