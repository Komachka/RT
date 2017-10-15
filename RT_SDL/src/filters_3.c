/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:00:07 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:20:22 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

unsigned int	rand_interval(unsigned int min, unsigned int max)
{
	int				r;
	unsigned int	range;
	unsigned int	buckets;
	unsigned int	limit;

	range = 1 + max - min;
	buckets = RAND_MAX / range;
	limit = buckets * range;
	r = rand();
	while (r >= (int)limit)
		r = rand();
	return (min + (r / buckets));
}

void			ft_rgb(t_rtv *rtv, int x)
{
	int	y;
	int	image_x;
	int	image_y;

	y = 0;
	while (y < WY)
	{
		image_x = rand_interval(x, x + 5);
		image_y = rand_interval(y, y + 5);
		if (image_x < WX && image_y < WY)
		{
			rtv->filter.sdl_col_with_filter[y][x].r =
				rtv->filter.sdl_col_with_filter[image_y][image_x].r;
			rtv->filter.sdl_col_with_filter[y][x].g =
				rtv->filter.sdl_col_with_filter[image_y][image_x].g;
			rtv->filter.sdl_col_with_filter[y][x].b =
				rtv->filter.sdl_col_with_filter[image_y][image_x].b;
		}
		y++;
	}
}

void			create_glass_filter(t_rtv *rtv)
{
	int	x;

	x = 0;
	while (x < WX)
	{
		ft_rgb(rtv, x);
		x++;
	}
}

void			ft_rgb2(t_rtv *rtv, int x)
{
	int	y;
	int	image_x;
	int	image_y;

	y = 0;
	while (y < WY)
	{
		image_x = randon(x, x + 5);
		image_y = randon(y, y + 5);
		if (image_x < WX && image_y < WY)
		{
			rtv->filter.sdl_col_with_filter[y][x].r =
				rtv->filter.sdl_col_with_filter[image_y][image_x].r;
			rtv->filter.sdl_col_with_filter[y][x].g =
				rtv->filter.sdl_col_with_filter[image_y][image_x].g;
			rtv->filter.sdl_col_with_filter[y][x].b =
				rtv->filter.sdl_col_with_filter[image_y][image_x].b;
		}
		y++;
	}
}

void			create_sromanets(t_rtv *rtv)
{
	int	k;
	int	x;

	k = 0;
	while (k < 5)
	{
		x = 0;
		while (x < WX)
		{
			ft_rgb2(rtv, x);
			x++;
		}
		k++;
	}
}
