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
	rtv->bg_color = OFF;
	rtv->background_color = create_color("FFEFD5");
	rtv->light_model = LAMBERT;
	rtv->recursive_depth = 3;

	rtv->samples_grid = 1; // ніколи не може бути меншим за 1 !!!!, задається в карті
	rtv->samples_per_pixel = pow(rtv->samples_grid, 2);
	rtv->delta_aliasing = 1.0 / (2.0 * rtv->samples_grid);
	
	rtv->air_coef = 1.00029;

	set_camera(&rtv->cam, create_vector(0, 0, 0), create_vector(0, 0, 0), STANDART, 45, 1, 270);
	if (k == '1')
		scene_1(rtv);
	
}

void	usage(void)
{
	//написати нормальний usage !!!
	char *s;

	s = "usage: ./RT scene_number\n\t1 - Sphere;\n\t2 - Cone;\
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
