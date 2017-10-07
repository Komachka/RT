/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:14:16 by askochul          #+#    #+#             */
/*   Updated: 2017/09/28 16:14:27 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_color	create_color(char *hex)
{
	t_color		cl;

	set_zero_color(&cl);
	if (hex)
		cl = parse_color(ft_atoi_base(hex, 16));
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
