/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:19:53 by kzahreba          #+#    #+#             */
/*   Updated: 2017/09/27 21:20:31 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	ft_init_texture_rect(t_rtv *rtv)
{
	rtv->rect_rt.x = 0;
	rtv->rect_rt.y = 0;
	rtv->rect_rt.w = 1000;
	rtv->rect_rt.h = 1000;
}

void	ft_redraw(t_rtv *rtv)
{
	SDL_RenderClear(rtv->renderer);
	threads(rtv);
	copy_to_filter(rtv);
	if (rtv->filter.black_and_white > 0)
		create_b_n_w_filter(rtv);
	if (rtv->filter.blur > 0)
		create_blur_filter(rtv, 0.0, 0.0, 0.0);
	if (rtv->filter.glass > 0)
		create_glass_filter(rtv);
	if (rtv->filter.emboss > 0)
		create_emboss_filter(rtv, 0.0, 0.0, 0.0);
	if (rtv->filter.sepia > 0)
		create_sepia_filter(rtv, 0, 0, 0);
	if (rtv->filter.negative > 0)
		create_negative_filter(rtv);
	if (rtv->filter.romanets > 0)
		create_sromanets(rtv);
	create_rander_texture(rtv);
	SDL_RenderClear(rtv->renderer);
	SDL_RenderCopy(rtv->renderer, rtv->sdl_texture_render, NULL, &rtv->rect_rt);
	SDL_RenderPresent(rtv->renderer);
}

void	ft_draw(t_rtv *rtv)
{
	int j;
	int x;

	j = 0;
	while (j < WY)
	{
		x = 0;
		while (x < WX)
		{
			SDL_SetRenderDrawColor(rtv->renderer, rtv->s_c[j][x].r,\
					rtv->s_c[j][x].g, rtv->s_c[j][x].b, rtv->s_c[j][x].a);
			SDL_RenderDrawPoint(rtv->renderer, x, j);
			x++;
		}
		j++;
	}
}

void	ft_action(t_rtv *rtv)
{
	rtv->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,\
			SDL_WINDOWPOS_CENTERED, WX, WY, SDL_WINDOW_OPENGL);
	rtv->window_id = SDL_GetWindowID(rtv->window);
	rtv->renderer = SDL_CreateRenderer(rtv->window,\
			-1, SDL_RENDERER_ACCELERATED);
	load_texture1(rtv);
	//uploading_textures(rtv) загрузка текстур з картинки в массив
	SDL_RenderClear(rtv->renderer);
	threads(rtv);
	copy_to_filter(rtv);
	create_rander_texture(rtv);
	ft_init_texture_rect(rtv);
	SDL_RenderCopy(rtv->renderer, rtv->sdl_texture_render, NULL, &rtv->rect_rt);
	SDL_RenderPresent(rtv->renderer);
}

void	basic_function(t_rtv *rtv)
{
	int	y;
	int	done;

	y = -1;
	done = 0;
	rtv->len = WX * WY * 4 - 1;
	ft_action(rtv);
	while (!done)
	{
		while (SDL_PollEvent(&rtv->e))
		{
			if ((rtv->e.key.keysym.sym == SDLK_ESCAPE ||\
						rtv->e.type == SDL_QUIT) &&\
					rtv->e.window.windowID == rtv->window_id)
				done = 1;
			else if (rtv->e.type == SDL_KEYUP)
				my_key_funct(rtv);
		}
	}
	delstruct(rtv);
}