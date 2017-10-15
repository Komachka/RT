/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:56:28 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 21:19:51 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	ft_menu(t_menu *menu, t_rtv *rtv)
{
	int done;
	int x_mouse;
	int y_mouse;
	int i;

	done = 0;
	ft_create_menu_window(menu);
	ft_render_copy(menu);
	SDL_RenderPresent(menu->renderer);
	while (!done)
	{
		while (SDL_PollEvent(&menu->e))
		{
			if (((menu->e.type == SDL_KEYDOWN &&
							menu->e.key.keysym.sym == SDLK_ESCAPE)
						|| menu->e.window.event == SDL_WINDOWEVENT_CLOSE)
					&& menu->window_id == menu->e.window.windowID)
				delstruct1(menu);
			if (menu->e.type == SDL_MOUSEMOTION)
				ft_mouse_motion(menu, rtv, x_mouse, y_mouse);
			if (menu->e.button.button == SDL_BUTTON_LEFT)
				ft_left_button(menu, rtv, x_mouse, y_mouse);
		}
	}
}
