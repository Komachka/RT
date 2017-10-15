/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:56:28 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 21:28:17 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	ft_init_rects_2(t_menu *menu)
{
	menu->boxes[6].rect.x = 975;
	menu->boxes[6].rect.y = 400;
	menu->boxes[6].rect.w = 350;
	menu->boxes[6].rect.h = 270;
}

void	ft_init_rects(t_menu *menu)
{
	menu->boxes[0].rect.x = 0;
	menu->boxes[0].rect.y = 0;
	menu->boxes[0].rect.w = 1400;
	menu->boxes[0].rect.h = 1000;
	menu->boxes[1].rect.x = 160;
	menu->boxes[1].rect.y = 30;
	menu->boxes[1].rect.w = 350;
	menu->boxes[1].rect.h = 270;
	menu->boxes[2].rect.x = 550;
	menu->boxes[2].rect.y = 15;
	menu->boxes[2].rect.w = 330;
	menu->boxes[2].rect.h = 270;
	menu->boxes[3].rect.x = 940;
	menu->boxes[3].rect.y = 30;
	menu->boxes[3].rect.w = 350;
	menu->boxes[3].rect.h = 270;
	menu->boxes[4].rect.x = 125;
	menu->boxes[4].rect.y = 400;
	menu->boxes[4].rect.w = 350;
	menu->boxes[4].rect.h = 270;
	menu->boxes[5].rect.x = 530;
	menu->boxes[5].rect.y = 380;
	menu->boxes[5].rect.w = 350;
	menu->boxes[5].rect.h = 270;
	ft_init_rects_2(menu);
}

void	ft_init_textures(t_menu *menu)
{
	menu->boxes[0].scene = IMG_LoadTexture(menu->renderer,
			"/image/fone21.png");
	menu->boxes[1].scene = IMG_LoadTexture(menu->renderer,
			"/image/scene_2.BMP");
	menu->boxes[2].scene = IMG_LoadTexture(menu->renderer,
			"/image/scene_1.jpg");
	menu->boxes[3].scene = IMG_LoadTexture(menu->renderer,
			"/image/scene_1.jpg");
	menu->boxes[4].scene = IMG_LoadTexture(menu->renderer,
			"/image/scene_1.jpg");
	menu->boxes[5].scene = IMG_LoadTexture(menu->renderer,
			"/image/scene_1.jpg");
	menu->boxes[6].scene = IMG_LoadTexture(menu->renderer,
			"/image/scene_1.jpg");
}

void	ft_render_copy(t_menu *menu)
{
	int i;

	i = 6;
	while (i >= 0)
	{
		if (SDL_RenderCopy(menu->renderer, menu->boxes[i].scene, NULL,
					&menu->boxes[i].rect) < 0)
		{
			SDL_Log("%s", SDL_GetError());
			return ;
		}
		i--;
	}
}

void	ft_which_scene(t_rtv *rtv, int i)
{
	char	*scene_name;
	char	*end;
	char	*name;
	char	*nbr;

	nbr = ft_itoa(i);
	name = join("scene", nbr);
	free(nbr);
	end = ".json";
	scene_name = join(name, end);
	free(name);
	cJSON_Delete(rtv->obj);
	get_scene(scene_name, rtv);
	free(scene_name);
}
