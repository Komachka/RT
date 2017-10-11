/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 19:58:01 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 21:49:33 by askochul         ###   ########.fr       */
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
	free_textures(rtv);
	SDL_FreeSurface(rtv->surface_main);
	SDL_DestroyRenderer(rtv->renderer);
	SDL_DestroyWindow(rtv->window);
}

void	delstruct1(t_menu *menu)
{
	int i;

	i = 1;
	while (i <= SCENSES)
	{
		if (menu->boxes[i].scene != NULL)
			SDL_DestroyTexture(menu->boxes[i].scene);
		else
			SDL_Log("%s", SDL_GetError());
		i++;
	}
	SDL_DestroyRenderer(menu->renderer);
	SDL_DestroyWindow(menu->window);
	IMG_Quit();
	SDL_Quit();
	exit(0);
}
