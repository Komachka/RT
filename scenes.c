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
	rtv->figure_num = 2;
	rtv->objects = (t_figure *)malloc(sizeof(t_figure) * rtv->figure_num);
	fill_sphere(&rtv->objects[0], create_vector(0, 0, 100), 20);
	set_material(&rtv->objects[0], create_vector(0.2, 1, 0.7), 7, "ff30a2");
	fill_plane(&rtv->objects[1], create_vector(100, 800, 300), \
		create_vector(0, 40, 1));
	set_material(&rtv->objects[1], create_vector(0.2, 1, 0), 9, "f2efae");
}

void	scene_2(t_rtv *rtv)
{
	rtv->figure_num = 2;
	rtv->objects = (t_figure *)malloc(sizeof(t_figure) * rtv->figure_num);
	fill_cone(&rtv->objects[0], create_vector(0, 40, 300), \
		create_vector(0, 1, 0), 22);
	set_material(&rtv->objects[0], create_vector(0.2, 1, 1), 5, "630684");
	fill_plane(&rtv->objects[1], create_vector(100, 800, 300), \
		create_vector(0, 40, 1));
	set_material(&rtv->objects[1], create_vector(0.2, 1, 0), 9, "ccccff");
}

void	scene_3(t_rtv *rtv)
{
	rtv->figure_num = 2;
	rtv->objects = (t_figure *)malloc(sizeof(t_figure) * rtv->figure_num);
	fill_cylinder(&rtv->objects[0], create_vector(500, 500, 280), \
		create_vector(1, 4, 0), 90);
	set_material(&rtv->objects[0], create_vector(0.2, 1, 1), 10, "0031e2");
	fill_plane(&rtv->objects[1], create_vector(100, 800, 300), \
		create_vector(0, 40, 1));
	set_material(&rtv->objects[1], create_vector(0.2, 1, 0), 9, "efd481");
}

void	scene_4(t_rtv *rtv)
{
	rtv->figure_num = 4;
	rtv->objects = (t_figure *)malloc(sizeof(t_figure) * rtv->figure_num);
	fill_sphere(&rtv->objects[0], create_vector(300, 250, 100), 90);
	set_material(&rtv->objects[0], create_vector(0.1, 1, 1), 8, "BB0000");
	fill_cone(&rtv->objects[1], create_vector(800, 400, 300), \
		create_vector(0, 1, 0), 22);
	set_material(&rtv->objects[1], create_vector(0.1, 1, 1), 5, "008A00");
	fill_plane(&rtv->objects[2], create_vector(100, 800, 300), \
		create_vector(0, 40, 1));
	set_material(&rtv->objects[2], create_vector(0.2, 1, 0), 9, "F0A30A");
	fill_cylinder(&rtv->objects[3], create_vector(500, 500, 280), \
		create_vector(1, -4, 0), 80);
	set_material(&rtv->objects[3], create_vector(0.2, 1, 1), 10, "0050EF");
}

void	scene_5(t_rtv *rtv)
{
	rtv->figure_num = 7;
	rtv->objects = (t_figure *)malloc(sizeof(t_figure) * rtv->figure_num);
	fill_sphere(&rtv->objects[0], create_vector(320, 450, 40), 90);
	set_material(&rtv->objects[0], create_vector(0.2, 1, 0), 0, "00cc99");
	fill_plane(&rtv->objects[1], create_vector(100, 800, 300), \
		create_vector(0, 40, 1));
	set_material(&rtv->objects[1], create_vector(0.2, 1, 0), 9, "ffcc99");
	fill_plane(&rtv->objects[2], create_vector(-100, 50, -300), \
		create_vector(-0, -40, -1));
	set_material(&rtv->objects[2], create_vector(0.2, 1, 0), 9, "ffcc99");
	fill_plane(&rtv->objects[3], create_vector(100, 800, 2000), \
		create_vector(0, 0, -1));
	set_material(&rtv->objects[3], create_vector(0.2, 1, 0), 9, "ffff99");
	fill_plane(&rtv->objects[4], create_vector(100, 40, 0), \
		create_vector(1, 0, 0));
	set_material(&rtv->objects[4], create_vector(0.2, 1, 0), 9, "ffcc99");
	fill_plane(&rtv->objects[5], create_vector(900, 40, 0), \
		create_vector(-1, 0, 0));
	set_material(&rtv->objects[5], create_vector(0.2, 1, 0), 9, "ffcc99");
	fill_cone(&rtv->objects[6], create_vector(500, 400, 300), \
		create_vector(-2, 5, 0), 22);
	set_material(&rtv->objects[6], create_vector(0.2, 1, 1), 5, "630684");
}
