/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 19:09:41 by kstorozh          #+#    #+#             */
/*   Updated: 2017/10/15 12:46:27 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static int			sdl_thread(void *ptr)
{
	SDL_Rect	rect;
	static int	n_frame2;
	SDL_Rect	rect1;
	t_rtv		*rtv;

	rtv = (t_rtv*)ptr;
	n_frame2 = 0;
	rect1.x = 0;
	rect1.y = 0;
	rect1.w = WX;
	rect1.h = WY;
	rect.w = 200;
	rect.h = 200;
	rect.x = WX / 2 - rect.w / 2;
	rect.y = WY / 2 - rect.h / 2;
	SDL_RenderClear(rtv->renderer);
	SDL_RenderCopy(rtv->renderer, rtv->sdl_texture_render, NULL, &rect1);
	SDL_RenderCopy(rtv->renderer, rtv->sdl_texture_loading[n_frame2 / 8],
			NULL, &rect);
	n_frame2++;
	if (n_frame2 / 8 >= 54)
		n_frame2 = 0;
	SDL_RenderPresent(rtv->renderer);
	return (0);
}

int					animation(SDL_Renderer *renderer, t_rtv *rtv)
{
	SDL_Thread	*thread;
	int			thread_return_value;

	thread = SDL_CreateThread(sdl_thread, "sdl_thread", (void*)rtv);
	if (NULL == thread)
		SDL_Log("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	else
		SDL_WaitThread(thread, &thread_return_value);
	return (0);
}

static inline void	load_texture3(t_rtv *rtv)
{
	rtv->sdl_texture_loading[46] = IMG_LoadTexture(rtv->renderer, "gif/46.png");
	rtv->sdl_texture_loading[47] = IMG_LoadTexture(rtv->renderer, "gif/47.png");
	rtv->sdl_texture_loading[48] = IMG_LoadTexture(rtv->renderer, "gif/48.png");
	rtv->sdl_texture_loading[49] = IMG_LoadTexture(rtv->renderer, "gif/49.png");
	rtv->sdl_texture_loading[50] = IMG_LoadTexture(rtv->renderer, "gif/50.png");
	rtv->sdl_texture_loading[51] = IMG_LoadTexture(rtv->renderer, "gif/51.png");
	rtv->sdl_texture_loading[52] = IMG_LoadTexture(rtv->renderer, "gif/52.png");
	rtv->sdl_texture_loading[53] = IMG_LoadTexture(rtv->renderer, "gif/53.png");
}

static inline void	load_texture2(t_rtv *rtv)
{
	rtv->sdl_texture_loading[22] = IMG_LoadTexture(rtv->renderer, "gif/22.png");
	rtv->sdl_texture_loading[23] = IMG_LoadTexture(rtv->renderer, "gif/23.png");
	rtv->sdl_texture_loading[24] = IMG_LoadTexture(rtv->renderer, "gif/24.png");
	rtv->sdl_texture_loading[25] = IMG_LoadTexture(rtv->renderer, "gif/25.png");
	rtv->sdl_texture_loading[26] = IMG_LoadTexture(rtv->renderer, "gif/26.png");
	rtv->sdl_texture_loading[27] = IMG_LoadTexture(rtv->renderer, "gif/27.png");
	rtv->sdl_texture_loading[28] = IMG_LoadTexture(rtv->renderer, "gif/28.png");
	rtv->sdl_texture_loading[29] = IMG_LoadTexture(rtv->renderer, "gif/29.png");
	rtv->sdl_texture_loading[30] = IMG_LoadTexture(rtv->renderer, "gif/30.png");
	rtv->sdl_texture_loading[31] = IMG_LoadTexture(rtv->renderer, "gif/31.png");
	rtv->sdl_texture_loading[32] = IMG_LoadTexture(rtv->renderer, "gif/32.png");
	rtv->sdl_texture_loading[33] = IMG_LoadTexture(rtv->renderer, "gif/33.png");
	rtv->sdl_texture_loading[34] = IMG_LoadTexture(rtv->renderer, "gif/34.png");
	rtv->sdl_texture_loading[35] = IMG_LoadTexture(rtv->renderer, "gif/35.png");
	rtv->sdl_texture_loading[36] = IMG_LoadTexture(rtv->renderer, "gif/36.png");
	rtv->sdl_texture_loading[37] = IMG_LoadTexture(rtv->renderer, "gif/37.png");
	rtv->sdl_texture_loading[38] = IMG_LoadTexture(rtv->renderer, "gif/38.png");
	rtv->sdl_texture_loading[39] = IMG_LoadTexture(rtv->renderer, "gif/39.png");
	rtv->sdl_texture_loading[40] = IMG_LoadTexture(rtv->renderer, "gif/40.png");
	rtv->sdl_texture_loading[41] = IMG_LoadTexture(rtv->renderer, "gif/41.png");
	rtv->sdl_texture_loading[42] = IMG_LoadTexture(rtv->renderer, "gif/42.png");
	rtv->sdl_texture_loading[43] = IMG_LoadTexture(rtv->renderer, "gif/43.png");
	rtv->sdl_texture_loading[44] = IMG_LoadTexture(rtv->renderer, "gif/44.png");
	rtv->sdl_texture_loading[45] = IMG_LoadTexture(rtv->renderer, "gif/45.png");
}

void				load_texture(t_rtv *rtv)
{
	load_texture2(rtv);
	load_texture3(rtv);
	rtv->sdl_texture_loading[0] = IMG_LoadTexture(rtv->renderer, "gif/0.png");
	rtv->sdl_texture_loading[1] = IMG_LoadTexture(rtv->renderer, "gif/1.png");
	rtv->sdl_texture_loading[2] = IMG_LoadTexture(rtv->renderer, "gif/2.png");
	rtv->sdl_texture_loading[3] = IMG_LoadTexture(rtv->renderer, "gif/3.png");
	rtv->sdl_texture_loading[4] = IMG_LoadTexture(rtv->renderer, "gif/4.png");
	rtv->sdl_texture_loading[5] = IMG_LoadTexture(rtv->renderer, "gif/5.png");
	rtv->sdl_texture_loading[6] = IMG_LoadTexture(rtv->renderer, "gif/6.png");
	rtv->sdl_texture_loading[7] = IMG_LoadTexture(rtv->renderer, "gif/7.png");
	rtv->sdl_texture_loading[8] = IMG_LoadTexture(rtv->renderer, "gif/8.png");
	rtv->sdl_texture_loading[9] = IMG_LoadTexture(rtv->renderer, "gif/9.png");
	rtv->sdl_texture_loading[10] = IMG_LoadTexture(rtv->renderer, "gif/10.png");
	rtv->sdl_texture_loading[11] = IMG_LoadTexture(rtv->renderer, "gif/11.png");
	rtv->sdl_texture_loading[12] = IMG_LoadTexture(rtv->renderer, "gif/12.png");
	rtv->sdl_texture_loading[13] = IMG_LoadTexture(rtv->renderer, "gif/13.png");
	rtv->sdl_texture_loading[14] = IMG_LoadTexture(rtv->renderer, "gif/14.png");
	rtv->sdl_texture_loading[15] = IMG_LoadTexture(rtv->renderer, "gif/15.png");
	rtv->sdl_texture_loading[16] = IMG_LoadTexture(rtv->renderer, "gif/16.png");
	rtv->sdl_texture_loading[17] = IMG_LoadTexture(rtv->renderer, "gif/17.png");
	rtv->sdl_texture_loading[18] = IMG_LoadTexture(rtv->renderer, "gif/18.png");
	rtv->sdl_texture_loading[19] = IMG_LoadTexture(rtv->renderer, "gif/19.png");
	rtv->sdl_texture_loading[20] = IMG_LoadTexture(rtv->renderer, "gif/20.png");
	rtv->sdl_texture_loading[21] = IMG_LoadTexture(rtv->renderer, "gif/21.png");
}
