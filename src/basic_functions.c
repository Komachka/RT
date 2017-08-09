/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:19:53 by kzahreba          #+#    #+#             */
/*   Updated: 2017/04/22 17:20:16 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		expose_hook(void *r)
{
	t_rtv *rtv;

	rtv = (t_rtv *)r;
	mlx_clear_window(rtv->mlx, rtv->win);
	mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
	return (0);
}

int		mouse_hook(int bn, int x, int y, t_rtv *rtv)
{
	if (x >= 0 && x <= WX && y >= 0 && y <= WY)
	{
		if (bn >= 4 && bn <= 7)
		{
			if (bn == 7)
				rtv->cam.pos.x -= 5;
			else if (bn == 6)
				rtv->cam.pos.x += 5;
			else if (bn == 5)
				rtv->cam.pos.y += 5;
			else if (bn == 4)
				rtv->cam.pos.y -= 5;
			new_image(rtv);
			threads(rtv);
			mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
		}
	}
	return (0);
}

void	key_funct_2(int k, t_rtv *rtv)
{
	if (k == 49)
		rtv->lightening = rtv->lightening == 0 ? 1 : 0;
	else if (k == 69)
		rtv->cam.pos.z += 5;
	else if (k == 78)
		rtv->cam.pos.z -= 5;
	else if (k == 35)
		set_zero_vect(&rtv->cam.pos);
	else if (k == 15)
	{
		rtv->cam.rotate[X] = 0;
		rtv->cam.rotate[Y] = 0;
		rtv->cam.rotate[Z] = 0;
	}
}

void	key_funct_1(int k, t_rtv *rtv)
{
	if (k == 125)
		rtv->cam.rotate[X] += 0.1;
	else if (k == 126)
		rtv->cam.rotate[X] -= 0.1;
	else if (k == 115)
		rtv->cam.rotate[Z] += 0.1;
	else if (k == 119)
		rtv->cam.rotate[Z] -= 0.1;
	else if (k == 124)
		rtv->cam.rotate[Y] -= 0.1;
	else if (k == 123)
		rtv->cam.rotate[Y] += 0.1;
}

void	key_funct_3(int k, t_rtv *rtv)
{
	if (k == 24 && rtv->light_model == LAMBERT)
		rtv->global_light.intensity = calculate_color(1.2, \
			&rtv->global_light.intensity);
	else if (k == 27 && rtv->light_model == LAMBERT)
		rtv->global_light.intensity = calculate_color(0.8, \
			&rtv->global_light.intensity);
	else if (k == 18)
		rtv->light_model = LAMBERT;
	else if (k == 19)
		rtv->light_model = CARTOON;
}

int		my_key_funct(int k, t_rtv *rtv)
{
	if (k == 53)
		delstruct(rtv);
	key_funct_1(k, rtv);
	key_funct_2(k, rtv);
	key_funct_3(k, rtv);
	new_image(rtv);
	threads(rtv);
	mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
	return (0);
}

void	basic_function(t_rtv *rtv)
{
	int i;
	int n;
	int end;
	int y;

	y = -1;
	rtv->len = WX * WY * 4 - 1;
	rtv->mlx = mlx_init();
	rtv->win = mlx_new_window(rtv->mlx, WX, WY, "RT");
	rtv->img = mlx_new_image(rtv->mlx, WX, WY);
	rtv->pic = mlx_get_data_addr(rtv->img, &i, &n, &end);
	threads(rtv);
	mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
	mlx_hook(rtv->win, 2, 5, my_key_funct, rtv);
	mlx_hook(rtv->win, 17, 0, end_function, 0);
	mlx_mouse_hook(rtv->win, mouse_hook, rtv);
	mlx_expose_hook(rtv->win, expose_hook, rtv);
	mlx_loop(rtv->mlx);
}
