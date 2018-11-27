/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 19:58:01 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/15 12:48:42 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double				min(double i, double j)
{
	double a;

	a = i > j ? j : i;
	return (a);
}

t_vect				adding_bias(t_vect *point, t_vect *dir)
{
	t_vect b;

	b = vector_mult(BIAS, dir);
	return (vector_add(point, &b));
}

static inline void	del_arrey(void **arrey, int size)
{
	int i;

	i = 0;
	while (i <= size)
	{
		if (arrey[i] != NULL)
			free(arrey[i]);
		i++;
	}
	if (arrey != NULL)
		free(arrey);
}

void				delstruct(t_rtv *rtv)
{
	free_textures(rtv);
	free_animation_texture(rtv);
	del_arrey((void**)rtv->s_c, WY);
	del_arrey((void**)rtv->filter.sdl_col_with_filter, WY);
	SDL_FreeSurface(rtv->surface_main);
	SDL_FreeSurface(rtv->picture);
	SDL_FreeSurface(rtv->surface);
	SDL_DestroyTexture(rtv->sdl_texture_render);
	SDL_DestroyTexture(rtv->surface_texture);
	SDL_DestroyTexture(rtv->hooks);
	SDL_RenderClear(rtv->renderer);
	SDL_DestroyRenderer(rtv->renderer);
	SDL_DestroyWindow(rtv->window);
	free_rtv(rtv);
}

void				delstruct1(t_menu *menu)
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
}
