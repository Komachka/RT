/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:19:53 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/15 12:50:56 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	malloc_sdl_colour(t_rtv *rtv)
{
	SDL_Color	**colours;
	SDL_Color	**colours2;
	int			i;

	colours = (SDL_Color**)malloc(sizeof(SDL_Color*) * WY);
	i = 0;
	while (i <= WY)
	{
		colours[i] = (SDL_Color*)malloc(sizeof(SDL_Color) * WX);
		i++;
	}
	rtv->s_c = colours;
	colours2 = (SDL_Color**)malloc(sizeof(SDL_Color*) * WY);
	i = 0;
	while (i <= WY)
	{
		colours2[i] = (SDL_Color*)malloc(sizeof(SDL_Color) * WX);
		i++;
	}
	rtv->filter.sdl_col_with_filter = colours2;
}

static inline void	ft_init_texture_rect(t_rtv *rtv)
{
	rtv->rect_rt.x = 0;
	rtv->rect_rt.y = 0;
	rtv->rect_rt.w = WX;
	rtv->rect_rt.h = WY;
}

void				ft_redraw(t_rtv *rtv)
{
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

static inline void	ft_action(t_rtv *rtv)
{
	rtv->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,\
			SDL_WINDOWPOS_CENTERED, WX, WY, SDL_WINDOW_OPENGL);
	rtv->window_id = SDL_GetWindowID(rtv->window);
	rtv->renderer = SDL_CreateRenderer(rtv->window,\
			-1, SDL_RENDERER_ACCELERATED);
	load_texture(rtv);
	uploading_textures(rtv);
	SDL_RenderClear(rtv->renderer);
	malloc_sdl_colour(rtv);
	threads(rtv);
	copy_to_filter(rtv);
	rtv->surface_main = SDL_CreateRGBSurface(0, WX, WY, 32, 0, 0, 0, 0);
	create_rander_texture(rtv);
	ft_init_texture_rect(rtv);
	SDL_RenderCopy(rtv->renderer, rtv->sdl_texture_render, NULL, &rtv->rect_rt);
	SDL_RenderPresent(rtv->renderer);
}

void				basic_function(t_rtv *rtv)
{
	int	done;

	done = 0;
	rtv->len = WX * WY * 4 - 1;
	ft_action(rtv);
	while (!done)
	{
		while (SDL_PollEvent(&rtv->e))
		{
			if (((rtv->e.type == SDL_KEYDOWN &&
					rtv->e.key.keysym.sym == SDLK_ESCAPE) ||
					rtv->e.window.event == SDL_WINDOWEVENT_CLOSE) &&
					rtv->window_id == rtv->e.window.windowID)
			{
				done = 1;
			}
			else if (rtv->e.type == SDL_KEYUP)
				my_key_funct(rtv);
		}
	}
	delstruct(rtv);
}
