/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:13:35 by kzahreba          #+#    #+#             */
/*   Updated: 2017/07/05 19:13:57 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scene_1(t_rtv *rtv)
{
	rtv->figure_num = 6;
 	if (!(rtv->objects = (t_figure *)malloc(sizeof(t_figure) * rtv->figure_num)))
 		malloc_error();

	fill_sphere(&rtv->objects[0], create_vector(-15, 10, 120), 10);
	set_material(&rtv->objects[0], create_color_struct(0.8, 0.8, 0.8, 0), create_color_struct(1, 1, 1, 0), create_color_struct(1, 1, 1, 0), 8, "BB0000", 0.1, 0.8, 1.015);
	
	fill_cone(&rtv->objects[1], create_vector(20, 25, 180), \
		create_vector(0, 1, 0), 18);
	set_material(&rtv->objects[1], create_color_struct(1, 1, 1, 0), create_color_struct(1, 1, 1, 0), create_color_struct(0.3, 0.3, 1, 0), 5, "008A00", 0, 0, 0);
	
	fill_plane(&rtv->objects[2], create_vector(10, -50, 30), \
		create_vector(0, 40, 1));
	set_material(&rtv->objects[2], create_color_struct(0.5, 0.5, 0.5, 0), create_color_struct(1, 1, 1, 0), create_color_struct(0, 0, 0, 0), 9, "F0A30A", 0.2, 0, 0);
	
	fill_cylinder(&rtv->objects[3], create_vector(-30, 30, 180), \
		create_vector(1, 4, 14), 8);
	set_material(&rtv->objects[3], create_color_struct(1, 1, 1, 0), create_color_struct(1, 1, 1, 0), create_color_struct(0, 0, 0, 0), 7, "0050EF", 0, 0, 0);

	fill_torus(&rtv->objects[4], create_vector(30, 30, 220), create_vector(0, 0, 1), 8, 30);
	set_material(&rtv->objects[4], create_color_struct(1, 1, 1, 0), create_color_struct(1, 1, 1, 0), create_color_struct(0, 0, 0, 0), 7, "00CED1", 0, 0, 0);

	fill_triangle(&rtv->objects[5], create_vector(-15, 10, 120), create_vector(20, 25, 180), create_vector(30, -80, 30));
	set_material(&rtv->objects[5], create_color_struct(1, 1, 1, 0), create_color_struct(1, 1, 1, 0), create_color_struct(1, 1, 1, 0), 7, "00CED1", 0.9, 0, 0);

	rtv->light_num = 3;
	if(!(rtv->l = (t_light *)malloc(sizeof(t_light) * rtv->light_num)))
		malloc_error();
	fill_light(&rtv->global_light, 0, create_vector(0, 0, 0),  create_color_struct(0.2, 0.2, 0.2, 0), create_vector(0, 0, 0), create_vector(0, 0, 0), 0, 0);
	fill_light(&rtv->l[0], POINT_LIGHT, create_vector(80, 10, 0), create_color_struct(0.3, 0.3, 0.3, 0), create_vector(1, 0.0014, 0.000007), create_vector(0, 0, 0), 0, 0);
	fill_light(&rtv->l[1], SPOT_LIGHT, create_vector(20, -10, 0), create_color_struct(0.9, 0.9, 0.9, 0), create_vector(1, 0, 0), create_vector(0, 0.25, 1), 20, 5);
	fill_light(&rtv->l[2], DIRECTIONAL_LIGHT, create_vector(0, 0, 0), create_color_struct(0.1, 0.1, 0.1, 0), create_vector(0, 0, 0), create_vector(4, -10, 10), 0, 0);
}