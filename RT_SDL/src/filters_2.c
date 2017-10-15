/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:00:07 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:20:02 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void			create_negative_filter(t_rtv *rtv)
{
	int	i;
	int	j;

	i = 0;
	while (i < WY)
	{
		j = 0;
		while (j < WX)
		{
			rtv->filter.sdl_col_with_filter[i][j].r =
				255 - rtv->filter.sdl_col_with_filter[i][j].r;
			rtv->filter.sdl_col_with_filter[i][j].g =
				255 - rtv->filter.sdl_col_with_filter[i][j].g;
			rtv->filter.sdl_col_with_filter[i][j].b =
				255 - rtv->filter.sdl_col_with_filter[i][j].b;
			j++;
		}
		i++;
	}
}

void			foo_b(double *red, double *green, double *blue, t_tmp tmp)
{
	t_rtv			*rtv;
	int				image_x;
	int				image_y;
	static double	filter[fH][fW] = {{0, 0, 1, 0, 0}, {0, 1, 1, 1, 0},
		{1, 1, 1, 1, 1}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}};

	rtv = tmp.rtv;
	tmp.filterY = 0;
	while (tmp.filterY < fH)
	{
		tmp.filterX = 0;
		while (tmp.filterX < fW)
		{
			image_x = (tmp.x - fW / 2 + tmp.filterX + WX) % WX;
			image_y = (tmp.y - fH / 2 + tmp.filterY + WY) % WY;
			*red += rtv->filter.sdl_col_with_filter[image_y][image_x].r *
				filter[tmp.filterY][tmp.filterX];
			*green += rtv->filter.sdl_col_with_filter[image_y][image_x].g *
				filter[tmp.filterY][tmp.filterX];
			*blue += rtv->filter.sdl_col_with_filter[image_y][image_x].b *
				filter[tmp.filterY][tmp.filterX];
			tmp.filterX++;
		}
		tmp.filterY++;
	}
}

void			create_blur_filter(t_rtv *rtv, double red, double green,
		double blue)
{
	t_tmp tmp;

	tmp.x = 0;
	tmp.filterY = 0;
	tmp.filterX = 0;
	tmp.rtv = rtv;
	while (tmp.x < WX)
	{
		tmp.y = 0;
		while (tmp.y < WY)
		{
			red = 0.0;
			blue = 0.0;
			green = 0.0;
			foo_b(&red, &green, &blue, tmp);
			rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].r =
				MIN(MAX((double)(1.0 / 13.0) * red, 0), 255);
			rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].g =
				MIN(MAX((double)(1.0 / 13.0) * green, 0), 255);
			rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].b =
				MIN(MAX((double)(1.0 / 13.0) * blue, 0), 255);
			tmp.y++;
		}
		tmp.x++;
	}
}

void			foo_e(double *red, double *green, double *blue, t_tmp tmp)
{
	t_rtv			*rtv;
	int				image_x;
	int				image_y;
	static double	filter[fH][fW] = {{-1, 0, 0, 0, 0}, {0, -2, 0, 0, 0},
		{0, 0, 6, 0, 0}, {0, 0, 0, -2, 0}, {0, 0, 0, 0, -1}};

	rtv = tmp.rtv;
	tmp.filterY = 0;
	while (tmp.filterY < fH)
	{
		tmp.filterX = 0;
		while (tmp.filterX < fW)
		{
			image_x = (tmp.x - fW / 2 + tmp.filterX + WX) % WX;
			image_y = (tmp.y - fH / 2 + tmp.filterY + WY) % WY;
			*red += rtv->filter.sdl_col_with_filter[image_y][image_x].r *
				filter[tmp.filterY][tmp.filterX];
			*green += rtv->filter.sdl_col_with_filter[image_y][image_x].g *
				filter[tmp.filterY][tmp.filterX];
			*blue += rtv->filter.sdl_col_with_filter[image_y][image_x].b *
				filter[tmp.filterY][tmp.filterX];
			tmp.filterX++;
		}
		tmp.filterY++;
	}
}

void			create_emboss_filter(t_rtv *rtv, double red, double green,
		double blue)
{
	t_tmp tmp;

	tmp.x = 0;
	tmp.filterY = 0;
	tmp.filterX = 0;
	tmp.rtv = rtv;
	while (tmp.x < WX)
	{
		tmp.y = 0;
		while (tmp.y < WY)
		{
			red = 0.0;
			blue = 0.0;
			green = 0.0;
			foo_e(&red, &green, &blue, tmp);
			rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].r =
				MIN(MAX(red, 0), 255);
			rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].g =
				MIN(MAX(green, 0), 255);
			rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].b =
				MIN(MAX(blue, 0), 255);
			tmp.y++;
		}
		tmp.x++;
	}
}
