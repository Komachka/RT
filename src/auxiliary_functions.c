/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 19:58:01 by kzahreba          #+#    #+#             */
/*   Updated: 2017/05/18 21:54:42 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	min(double i, double j)
{
	double a;

	if (i > j)
		a = j;
	else
		a = i;
	return (a);
}

t_vect	adding_bias(t_vect *point, t_vect *dir)
{
	t_vect b;

	b = vector_mult(BIAS, dir);
	return (vector_add(point, &b));
}

int		quadratic_equation(t_equation *n, double *t)
{
	int i;

	i = 0;
	n->discr = n->b * n->b - 4 * n->a * n->c;
	if (n->discr >= 0)
	{
		n->sqdiscr = sqrt(n->discr);
		n->t0 = (-n->b + n->sqdiscr) / (2 * n->a);
		n->t1 = (-n->b - n->sqdiscr) / (2 * n->a);
		if (n->t0 > n->t1)
			n->t0 = n->t1;
		if (n->t0 > 0.000001f)
		{
			*t = n->t0;
			i = 1;
		}
	}
	return (i);
}

int		end_function(void)
{
	exit(1);
}

void	new_image(t_rtv *rtv)
{
	int i;
	int n;
	int end;

	mlx_destroy_image(rtv->mlx, rtv->img);
	rtv->img = mlx_new_image(rtv->mlx, WX, WY);
	rtv->pic = mlx_get_data_addr(rtv->img, &i, &n, &end);
}

double	degrees_to_radians(double x)
{
	return (M_PI * x / (double)180);
}

void	delstruct(t_rtv *rtv)
{
	mlx_clear_window(rtv->mlx, rtv->win);
	mlx_destroy_image(rtv->mlx, rtv->img);
	mlx_destroy_window(rtv->mlx, rtv->win);
	exit(0);
}
