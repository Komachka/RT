#include "rtv.h"


void ft_init_rects(t_menu *menu)
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
	menu->boxes[6].rect.x = 975;
	menu->boxes[6].rect.y = 400;
	menu->boxes[6].rect.w = 350;
	menu->boxes[6].rect.h = 270;
}


void ft_init_textures(t_menu *menu)
{
	menu->boxes[0].scene = IMG_LoadTexture(menu->renderer, "/image/fone1.png");

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

void ft_render_copy(t_menu *menu)
{
	int i = 6;
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
	char *scene_name;
	char *end;
	char *name;

	scene_name = "scene";
	end = ".json";
	name = join(scene_name, ft_itoa(i));
	name = join(name, end);
	get_scene(name, rtv);
}




void ft_menu(t_menu *menu, t_rtv *rtv)
{

	int done;
	int x_mouse;
	int y_mouse;

	done = 0;
<
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
	ft_render_copy(menu);

	SDL_RenderPresent(menu->renderer);

	while (!done)
	{
		while (SDL_PollEvent(&menu->e))
		{

			if (((menu->e.type == SDL_KEYDOWN && menu->e.key.keysym.sym == SDLK_ESCAPE) || menu->e.window.event == SDL_WINDOWEVENT_CLOSE) &&
				menu->window_id == menu->e.window.windowID)			
{

				int i = 1;
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

			if (menu->e.type == SDL_MOUSEMOTION)
			{
				x_mouse = menu->e.motion.x;
				y_mouse = menu->e.motion.y;

				int i = 1;

				while (i <= SCENSES)
				{
					if (x_mouse >= menu->boxes[i].rect.x && x_mouse <=
							menu->boxes[i].rect.x + menu->boxes[i].rect.w &&
							y_mouse >= menu->boxes[i].rect.y && y_mouse <=
							menu->boxes[i].rect.y + menu->boxes[i].rect.h)
					{
						SDL_SetTextureColorMod(menu->boxes[i].scene, 150, 150, 174);

						SDL_RenderClear(menu->renderer);
						ft_render_copy(menu);
						SDL_RenderPresent(menu->renderer);
					}
					else
					{
						SDL_SetTextureColorMod(menu->boxes[i].scene, 255, 255,
											   255);
						SDL_RenderClear(menu->renderer);
						ft_render_copy(menu);
						SDL_RenderPresent(menu->renderer);
					}
					i++;
				}

			}
			if (menu->e.button.button == SDL_BUTTON_LEFT)
			{
				x_mouse = menu->e.button.x;
				y_mouse = menu->e.button.y;
				int i = 1;

				while (i <= SCENSES)

				{
					if (x_mouse >= menu->boxes[i].rect.x && x_mouse <=
							menu->boxes[i].rect.x + menu->boxes[i].rect.w &&
							y_mouse >= menu->boxes[i].rect.y &&
							y_mouse <= menu->boxes[i].rect.y +
									menu->boxes[i].rect.h)
					{

						SDL_SetTextureColorMod(menu->boxes[i].scene, 250, 100,
											   100);
						SDL_RenderClear(menu->renderer);
						ft_render_copy(menu);
						SDL_RenderPresent(menu->renderer);
						ft_which_scene(rtv, i);

						basic_function(rtv);
					}
					i++;
				}

			}
		}
	}
}
