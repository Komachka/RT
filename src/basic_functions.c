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
	if (k == SPACE)
		rtv->lightening = rtv->lightening == 0 ? 1 : 0;
	if (k == KEY_B)
		rtv->bg_color = rtv->bg_color == 0 ? 1 : 0;
	else if (k == PLUS)
		rtv->cam.pos.z += 5;
	else if (k == MINUS)
		rtv->cam.pos.z -= 5;
	else if (k == KEY_P)
		set_zero_vect(&rtv->cam.pos);
	else if (k == KEY_R)
	{
		rtv->cam.rotate[X] = 0;
		rtv->cam.rotate[Y] = 0;
		rtv->cam.rotate[Z] = 0;
	}
}

void	key_funct_1(int k, t_rtv *rtv)
{
	if (k == DOWN)
		rtv->cam.rotate[X] += 0.1;
	else if (k == UP)
		rtv->cam.rotate[X] -= 0.1;
	else if (k == 115)
		rtv->cam.rotate[Z] += 0.1;
	else if (k == 119)
		rtv->cam.rotate[Z] -= 0.1;
	else if (k == RIGHT)
		rtv->cam.rotate[Y] -= 0.1;
	else if (k == LEFT)
		rtv->cam.rotate[Y] += 0.1;
}

void	key_funct_3(int k, t_rtv *rtv)
{
	if (k == TOP_PLUS && rtv->light_model == LAMBERT)
		rtv->global_light.intensity = calculate_color(1.2, \
			&rtv->global_light.intensity);
	else if (k == TOP_MINUS && rtv->light_model == LAMBERT)
		rtv->global_light.intensity = calculate_color(0.8, \
			&rtv->global_light.intensity);
	else if (k == TOP_NUM_1)
		rtv->light_model = LAMBERT;
	else if (k == TOP_NUM_2)
		rtv->light_model = CARTOON;
}

int		my_key_funct(int k, t_rtv *rtv)
{
	if (k == ESC)
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
