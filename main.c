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
	rtv->angles[0] = 0;
	rtv->angles[1] = 0;
	rtv->angles[2] = 0;
	rtv->lightening = 1;
	set_camera(&rtv->cam, create_vector(60, 40, -100), create_vector(0, 0, 0), 90);
	if (k == '1')
		scene_1(rtv);
	else if (k == '2')
		scene_2(rtv);
	else if (k == '3')
		scene_3(rtv);
	else if (k == '4')
		scene_4(rtv);
	else if (k == '5')
		scene_5(rtv);
	rtv->light_num = 3;
	rtv->l = (t_light *)malloc(sizeof(t_light) * rtv->light_num);
	fill_light(&rtv->l[0], create_vector(0, 100, -800), "FFFFFF");
	fill_light(&rtv->l[1], create_vector(0, 0, 500), "FFFFFF");
	fill_light(&rtv->l[2], create_vector(200, 100, -1500), "FFFFFF");
}

void	usage(void)
{
	char *s;

	s = "usage: ./Rtv1 scene_number\n\t1 - Sphere;\n\t2 - Cone;\
	\n\t3 - Cylinder;\n\t4 - Multiple objects;\n\t5 - Box;";
	ft_putendl(s);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_rtv		rtv;

	if (argc != 2)
		usage();
	if (ft_strlen(argv[1]) != 1 || *argv[1] < '1' || *argv[1] > '5')
		usage();
	fill_struct(&rtv, argv[1][0]);
	basic_function(&rtv);
	return (0);
}
