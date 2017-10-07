/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 19:58:01 by kzahreba          #+#    #+#             */
/*   Updated: 2017/09/28 16:13:28 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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

double	degrees_to_radians(double x)
{
	return (M_PI * x / (double)180);
}

void	delstruct(t_rtv *rtv)
{
	SDL_DestroyRenderer(rtv->renderer);
	SDL_DestroyWindow(rtv->window);
	SDL_FreeSurface(rtv->surface_main);
}

void	delstruct1(t_menu *menu)
{
	int i;

	i = 1;
	while (i < 10)
	{
		SDL_DestroyTexture(menu->boxes[i].scene);
		i++;
	}
	SDL_DestroyRenderer(menu->renderer);
	SDL_DestroyWindow(menu->window);
	IMG_Quit();
	SDL_Quit();
	exit(0);
}
