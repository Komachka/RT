/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 20:30:41 by kzahreba          #+#    #+#             */
/*   Updated: 2017/07/03 20:30:54 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void	fill_light(t_light *l, t_vect pos, char *color)
{
	if (l)
	{
		l->pos = pos;
		l->cl = create_color(color);
	}
}

void	set_camera(t_camera *cam, t_vect p, t_vect dir, double angle)
{
	cam->pos = p;
	cam->rotate[0] = M_PI * dir.x / 180;
	cam->rotate[1] = M_PI * dir.y / 180;
	cam->rotate[2] = M_PI * dir.z / 180;
	// printf("%f --x, %f --y, %f --z\n", cam->rotate[0], cam->rotate[1], cam->rotate[2]);
	// exit(0);
	cam->fov_h = M_PI * angle / 180;
	cam->image_aspect_ratio = (double)WX / (double)WY;
	cam->scale = tan(cam->fov_h / 2);
}

void	set_material(t_figure *f, t_vect ads, int shine, char *cl)
{
	f->material.ambient_strength = ads.x;
	f->material.diffuse_strength = ads.y;
	f->material.specular_strength = ads.z;
	f->material.shininess = shine;
	f->material.cl = create_color(cl);
}
