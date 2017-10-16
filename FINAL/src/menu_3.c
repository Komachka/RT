/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:56:28 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 21:28:00 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		open_author_file(void)
{
	system("open -a TextEdit author");
	return (0);
}

int		open_instruction_file(void)
{
	system("open -a Preview instruction-v1.png");
	return (0);
}

void	ft_create_menu_window(t_menu *menu)
{
	if ((menu->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
					SDL_WINDOW_OPENGL)) == NULL)
	{
		SDL_Log("%s", SDL_GetError());
		return ;
	}
	if ((menu->window_id = SDL_GetWindowID(menu->window)) == 0)
	{
		SDL_Log("%s", SDL_GetError());
		return ;
	}
	if ((menu->renderer = SDL_CreateRenderer(menu->window, -1,
					SDL_RENDERER_ACCELERATED)) == NULL)
	{
		SDL_Log("%s", SDL_GetError());
		return ;
	}
	ft_init_rects(menu);
	ft_init_textures(menu);
	if (SDL_RenderClear(menu->renderer) < 0)
	{
		SDL_Log("%s", SDL_GetError());
		return ;
	}
}

void	ft_left_button(t_menu *menu, t_rtv *rtv, int x_mouse, int y_mouse)
{
	int i;

	x_mouse = menu->e.button.x;
	y_mouse = menu->e.button.y;
	i = 1;
	while (i <= SCENSES)
	{
		if (x_mouse >= menu->boxes[i].rect.x && x_mouse <= menu->boxes[i].rect.x
				+ menu->boxes[i].rect.w && y_mouse >= menu->boxes[i].rect.y &&
				y_mouse <= menu->boxes[i].rect.y + menu->boxes[i].rect.h)
		{
			SDL_SetTextureColorMod(menu->boxes[i].scene, 250, 100, 100);
			SDL_RenderClear(menu->renderer);
			ft_render_copy(menu);
			SDL_RenderPresent(menu->renderer);
			ft_which_scene(rtv, i);
			basic_function(rtv);
		}
		if (x_mouse > 675 && x_mouse < 928 && y_mouse > 891 && y_mouse < 987)
			open_author_file();
		if (x_mouse > 375 && x_mouse < 600 && y_mouse > 891 && y_mouse < 987)
			open_instruction_file();
		i++;
	}
}

void	ft_mouse_motion(t_menu *menu, int x_mouse, int y_mouse)
{
	int i;

	x_mouse = menu->e.motion.x;
	y_mouse = menu->e.motion.y;
	i = 1;
	while (i <= SCENSES)
	{
		if (x_mouse >= menu->boxes[i].rect.x && x_mouse <= menu->boxes[i].rect.x
			+ menu->boxes[i].rect.w && y_mouse >= menu->boxes[i].rect.y &&
			y_mouse <= menu->boxes[i].rect.y + menu->boxes[i].rect.h)
		{
			SDL_SetTextureColorMod(menu->boxes[i].scene, 150, 150, 174);
			SDL_RenderClear(menu->renderer);
			ft_render_copy(menu);
			SDL_RenderPresent(menu->renderer);
		}
		else
		{
			SDL_SetTextureColorMod(menu->boxes[i].scene, 255, 255, 255);
			SDL_RenderClear(menu->renderer);
			ft_render_copy(menu);
			SDL_RenderPresent(menu->renderer);
		}
		i++;
	}
}
