/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 14:30:42 by kzahreba          #+#    #+#             */
/*   Updated: 2017/04/23 14:30:45 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	create_color(char *hex)
{
	int			color;
	t_color		cl;

	set_zero_color(&cl);
	if (hex)
	{
		color = ft_atoi_base(hex, 16);
		cl.b = (unsigned char)color / (double)255;
		cl.g = (unsigned char)(color >> 8) / (double)255;
		cl.r = (unsigned char)(color >> 16) / (double)255;
		cl.al = (unsigned char)(color >> 24) / (double)100;
	}
	return (cl);
}

t_color	calculate_color(double i, t_color *c)
{
	t_color	new;

	set_zero_color(&new);
	if (c)
	{
		new.r = c->r * i;
		new.g = c->g * i;
		new.b = c->b * i;
		new.al = c->al * i;
	}
	return (new);
}

t_color	create_color_struct(double r, double g, double b, double a)
{
	t_color v;

	v.r = r;
	v.g = g;
	v.b = b;
	v.al = a;
	return (v);
}

t_color	average_color(t_color *rt, int light_num)
{
	t_color	color;
	int		i;

	i = -1;
	set_zero_color(&color);
	if (rt)
	{
		while (++i < light_num)
		{
			color.r += rt[i].r;
			color.g += rt[i].g;
			color.b += rt[i].b;
			color.al += rt[i].al;
		}
		if (light_num)
			color = calculate_color(1.00 / (double)light_num, &color);
	}
	return (color);
}

t_color	proportional_color_distribution(t_color *cl1, t_color *cl2, double p1)
{
	t_color res;
	t_color tmp1;
	t_color tmp2;

	tmp1 = calculate_color(p1, cl1);
	tmp2 = calculate_color((1.00 - p1), cl2);
	res.r = tmp1.r + tmp2.r;
	res.g = tmp1.g + tmp2.g;
	res.b = tmp1.b + tmp2.b;
	res.al = tmp1.al + tmp2.al;
	return (res);
}

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
