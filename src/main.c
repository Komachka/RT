/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:11:38 by kzahreba          #+#    #+#             */
/*   Updated: 2017/06/08 18:11:14 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fill_struct(t_rtv *rtv, char k)
{
	rtv->lightening = ON;
	rtv->light_model = LAMBERT;
	rtv->reflective_depth = 1;
	set_camera(&rtv->cam, create_vector(0, 0, 0), create_vector(0, 0, 0), 45, 1);
	if (k == '1')
		scene_1(rtv);
	rtv->light_num = 3;
	if(!(rtv->l = (t_light *)malloc(sizeof(t_light) * rtv->light_num)))
		malloc_error();
	fill_light(&rtv->global_light, 0, create_vector(0, 0, 0),  create_color_struct(0.2, 0.2, 0.2, 0), create_vector(0, 0, 0), create_vector(0, 0, 0), 0, 0);
	fill_light(&rtv->l[0], POINT_LIGHT, create_vector(80, 10, 0), create_color_struct(0.3, 0.3, 0.3, 0), create_vector(1, 0.0014, 0.000007), create_vector(0, 0, 0), 0, 0);
	fill_light(&rtv->l[1], SPOT_LIGHT, create_vector(20, -10, 0), create_color_struct(0.9, 0.9, 0.9, 0), create_vector(1, 0, 0), create_vector(0, 0.25, 1), 20, 5);
	fill_light(&rtv->l[2], DIRECTIONAL_LIGHT, create_vector(0, 0, 0), create_color_struct(0.1, 0.1, 0.1, 0), create_vector(0, 0, 0), create_vector(4, -10, 10), 0, 0);
}

void	usage(void)
{
	//написати нормальний usage !!!
	char *s;

	s = "usage: ./Rtv1 scene_number\n\t1 - Sphere;\n\t2 - Cone;\
	\n\t3 - Cylinder;\n\t4 - Multiple objects;\n\t5 - Box;";
	ft_putendl(s);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_rtv		rtv;

	if (argc < 2)
		usage();
	if (ft_strlen(argv[1]) != 1 || *argv[1] < '1' || *argv[1] > '5')
		usage();
	fill_struct(&rtv, argv[1][0]);
	basic_function(&rtv);
	return (0);
}
