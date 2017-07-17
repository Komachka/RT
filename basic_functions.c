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
				rtv->cam.pos.x = rtv->cam.pos.x - 10;
			if (bn == 6)
				rtv->cam.pos.x = rtv->cam.pos.x + 10;
			if (bn == 5)
				rtv->cam.pos.y = rtv->cam.pos.y - 10;
			if (bn == 4)
				rtv->cam.pos.y = rtv->cam.pos.y + 10;
			new_image(rtv);
			threads(rtv);
			mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
		}
	}
	return (0);
}

int		my_key_funct_2(int k, t_rtv *rtv)
{
	if (k == 69)
		rtv->shift_z = rtv->shift_z + 200;
	if (k == 78)
		rtv->shift_z = rtv->shift_z - 200;
	if (k == 49)
		rtv->lightening = rtv->lightening == 0 ? 1 : 0;
	new_image(rtv);
	threads(rtv);
	mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
	return (0);
}

int		my_key_funct_1(int k, t_rtv *rtv)
{
	if (k == 53)
		delstruct(rtv);
	if ((k >= 123 && k <= 126) || k == 83 || k == 84)
	{
		if (k == 125)
			rtv->cam.rotate[0] = rtv->cam.rotate[0] + 0.1;
		if (k == 126)
			rtv->cam.rotate[0] = rtv->cam.rotate[0] - 0.1;
		if (k == 84)
			rtv->cam.rotate[2] = rtv->cam.rotate[2] + 0.1;
		if (k == 83)
			rtv->cam.rotate[2] = rtv->cam.rotate[2] - 0.1;
		if (k == 124)
			rtv->cam.rotate[1] = rtv->cam.rotate[1] + 0.1;
		if (k == 123)
			rtv->cam.rotate[1] = rtv->cam.rotate[1] - 0.1;
		new_image(rtv);
		threads(rtv);
		mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
	}
	if (k == 69 || k == 78 || k == 49)
		my_key_funct_2(k, rtv);
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
	rtv->win = mlx_new_window(rtv->mlx, WX, WY, "RTV1");
	rtv->img = mlx_new_image(rtv->mlx, WX, WY);
	rtv->pic = mlx_get_data_addr(rtv->img, &i, &n, &end);
	threads(rtv);
	mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->img, 0, 0);
	mlx_hook(rtv->win, 2, 5, my_key_funct_1, rtv);
	mlx_hook(rtv->win, 17, 0, end_function, 0);
	mlx_mouse_hook(rtv->win, mouse_hook, rtv);
	mlx_expose_hook(rtv->win, expose_hook, rtv);
	mlx_loop(rtv->mlx);
}
