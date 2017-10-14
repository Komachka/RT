/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:14:52 by askochul          #+#    #+#             */
/*   Updated: 2017/10/11 15:38:08 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_color	mult_color_coefs(t_color a, t_color b)
{
	t_color res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	res.al = a.al * b.al;
	return (res);
}

void	set_zero_color(t_color *cl)
{
	if (cl)
	{
		cl->r = 0;
		cl->g = 0;
		cl->b = 0;
		cl->al = 0;
	}
}

t_color	parse_color(int color)
{
	t_color cl;

	cl.b = (color & 255) / 255.0;
	cl.g = ((color >> 8) & 255) / 255.0;
	cl.r = ((color >> 16) & 255) / 255.0;
	cl.al = ((color >> 24) & 255) / 100.0;
	return (cl);
}
