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

	cl.r = 0;
	cl.g = 0;
	cl.b = 0;
	cl.al = 0;
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

t_color	average_color(t_color *rt, t_rtv *rtv)
{
	t_color	color;
	int		i;

	i = -1;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.al = 0;
	if (rt && rtv)
	{
		while (++i < rtv->light_num)
		{
			color.r += rt[i].r;
			color.g += rt[i].g;
			color.b += rt[i].b;
		}
		color.r = color.r / rtv->light_num;
		color.g = color.g / rtv->light_num;
		color.b = color.b / rtv->light_num;
	}
	return (color);
}

void	calculate_light(t_material *c, t_color *res, int shad)
{
	if (shad == 1)
	{
		res->r = c->cl.r * 0.2;
		res->g = c->cl.g * 0.2;
		res->b = c->cl.b * 0.2;
	}
	else
	{
		res->r = min((c->ambient.r + c->diffuse.r) * c->cl.r + \
			c->specular.r, 1);
		res->g = min((c->ambient.g + c->diffuse.g) * c->cl.g + \
			c->specular.g, 1);
		res->b = min((c->ambient.b + c->diffuse.b) * c->cl.b + \
			c->specular.b, 1);
	}
}

t_color	calculate_color(double i, t_color *c)
{
	t_color	new;

	new.r = c->r * i;
	new.g = c->b * i;
	new.b = c->b * i;
	return (new);
}
