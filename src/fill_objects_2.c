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

void	fill_light(t_light *l, int type, t_vect pos, t_color intensity, t_vect attenuation, t_vect direction, double angle, double outer_cut)
{
	if (l)
	{
		l->pos = pos;
		l->intensity = intensity;
		l->k_const = attenuation.x;
		l->k_linear = attenuation.y;
		l->k_quadratic = attenuation.z;
		l->type = type;
		l->direction = normalize_vector(&direction);
		l->outer_cone = cos(degrees_to_radians(angle / 2.0 + outer_cut));
		l->inner_cone = cos(degrees_to_radians(angle) / 2.0);
		l->epsilon = l->inner_cone - l->outer_cone;
	}
}

void	set_camera(t_camera *cam, t_vect p, t_vect angle, int type, double fv, double l_dir, double fy_andle)
{
	cam->pos = p;
	cam->rotate[X] = degrees_to_radians(angle.x);
	cam->rotate[Y] = degrees_to_radians(angle.y);
	cam->rotate[Z] = degrees_to_radians(angle.z);
	cam->image_aspect_ratio = (double)WX / (double)WY;
	cam->scale = tan(degrees_to_radians(fv) / 2);
	cam->type = type;
	cam->fisheye_angle = fy_andle;
	cam->lk_dir = l_dir;
}

void	set_material(t_figure *f, t_color am, t_color dif, t_color spec, double shine, char *cl, double reflective, double transparency, double refraction)
{
	f->material.ambient = am;
	f->material.diffuse = dif;
	f->material.specular = spec;
	f->material.shininess = shine;
	f->material.cl = create_color(cl);
	f->material.reflective = reflective;
	f->material.transparency = transparency;
	f->material.refraction = refraction;
	f->material.texture = 0;
}

// void  set_texture