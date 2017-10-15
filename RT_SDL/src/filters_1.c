/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:00:07 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:09:53 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int				randon(int low, int hight)
{
	double	scaled;

	scaled = (double)rand() / RAND_MAX;
	return (int)(low + (hight - low + 1) * scaled + low);
}

void			create_filter(t_rtv *rtv)
{
	t_filter	filter;

	filter.romanets = 0;
	filter.negative = 0;
	filter.sepia = 0;
	filter.emboss = 0;
	filter.glass = 0;
	filter.blur = 0;
	filter.black_and_white = 0;
	rtv->filter = filter;
}

void			copy_to_filter(t_rtv *rtv)
{
	int	i;
	int	j;

	i = 0;
	while (i <= WY)
	{
		j = 0;
		while (j <= WX)
		{
			rtv->filter.sdl_col_with_filter[i][j] = rtv->s_c[i][j];
			j++;
		}
		i++;
	}
}

void			create_sepia_filter(t_rtv *rtv, int red, int green, int blue)
{
	int	i;
	int	j;

	i = 0;
	while (i <= WY)
	{
		j = 0;
		while (j <= WX)
		{
			red = (0.393 * rtv->filter.sdl_col_with_filter[i][j].r + 0.769 *
					rtv->filter.sdl_col_with_filter[i][j].g + 0.189 *
					rtv->filter.sdl_col_with_filter[i][j].b);
			green = (0.349 * rtv->filter.sdl_col_with_filter[i][j].r + 0.686 *
					rtv->filter.sdl_col_with_filter[i][j].g + 0.168 *
					rtv->filter.sdl_col_with_filter[i][j].b);
			blue = (0.272 * rtv->filter.sdl_col_with_filter[i][j].r + 0.534 *
					rtv->filter.sdl_col_with_filter[i][j].g + 0.131 *
					rtv->filter.sdl_col_with_filter[i][j].b);
			rtv->filter.sdl_col_with_filter[i][j].r = MIN(red, 255);
			rtv->filter.sdl_col_with_filter[i][j].g = MIN(green, 255);
			rtv->filter.sdl_col_with_filter[i][j].b = MIN(blue, 255);
			j++;
		}
		i++;
	}
}

void			create_b_n_w_filter(t_rtv *rtv)
{
	int	i;
	int	j;
	int	midle;

	i = 0;
	midle = 0;
	while (i < WY)
	{
		j = 0;
		while (j < WX)
		{
			midle = (rtv->s_c[i][j].r + rtv->s_c[i][j].g +
					rtv->s_c[i][j].b) / 3;
			rtv->filter.sdl_col_with_filter[i][j].r = midle;
			rtv->filter.sdl_col_with_filter[i][j].g = midle;
			rtv->filter.sdl_col_with_filter[i][j].b = midle;
			j++;
		}
		i++;
	}
}
