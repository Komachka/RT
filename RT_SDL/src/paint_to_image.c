/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:43:23 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/04 18:01:33 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline char	*ft_strcat(char *s1, const char *s2)
{
	char		*dest;
	const char	*str2;
	int			i;
	int			k;

	i = 0;
	k = 0;
	dest = s1;
	str2 = s2;
	while (dest[i] != '\0')
		i++;
	while (str2[k] != '\0')
	{
		dest[i] = str2[k];
		i++;
		k++;
	}
	dest[i] = '\0';
	return (s1);
}

void				ft_take_picture(t_rtv *rtv)
{
	time_t	times;
	char	str[1000];

	str[0] = '\0';
	times = time(NULL);
	ft_strcat(str, "pictures/");
	ft_strcat(str, ctime(&times));
	SDL_SaveBMP(rtv->surface_main, ft_strcat(str, ".BMP"));
}

void				paint_image(t_rtv *fr, int x, int y, t_color cl)
{
	static int x1 = 0;
	static int y1 = 0;

	x1 = MAX(x, x1);
	y1 = MAX(y, y1);

	if (x >= WX || y >= WY)
		return ;

	fr->s_c[y][x].r = (unsigned char)(cl.r * 255);
	fr->s_c[y][x].g = (unsigned char)(cl.g * 255);
	fr->s_c[y][x].b = (unsigned char)(cl.b * 255);
	fr->s_c[y][x].a = (unsigned char)(cl.al * 100);

	
}



static inline void	put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 *pixels;

	pixels = (Uint32 *)surface->pixels;
	pixels[(y * surface->w) + x] = pixel;
}

void				create_rander_texture(t_rtv *rtv)
{
	rtv->surface_main = SDL_CreateRGBSurface(0, WX, WY, 32, 0, 0, 0, 0);
	for (int y = 0; y < WY; ++y)
	{
		for (int x = 0; x < WX ; ++x)
		{
			put_pixel(rtv->surface_main, x, y,
						SDL_MapRGBA(rtv->surface_main->format,
						rtv->filter.sdl_col_with_filter[y][x].r,
						rtv->filter.sdl_col_with_filter[y][x].g,
						rtv->filter.sdl_col_with_filter[y][x].b,
						rtv->filter.sdl_col_with_filter[y][x].a));
		}
	}
	if (rtv->sdl_texture_render != NULL)
		SDL_DestroyTexture(rtv->sdl_texture_render);
	rtv->sdl_texture_render = SDL_CreateTextureFromSurface(rtv->renderer, rtv->surface_main);
}
