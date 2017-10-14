/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:21:55 by askochul          #+#    #+#             */
/*   Updated: 2017/10/11 22:27:23 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	uploading_textures_2(t_rtv *rtv, t_mapping_texture *tx)
{
	char	*str;

	if (rtv->sk == ON && rtv->skybox.texturing == ON &&
			rtv->skybox.texture.type == MAPPING)
	{
		tx = (t_mapping_texture *)rtv->skybox.texture.tx_struct;
		str = join("image/", tx->img_path);
		if (!(tx->srf = IMG_Load(str)))
			put_error("Invalid path", str);
		tx->h = tx->srf->h;
		tx->w = tx->srf->w;
		tx->arr = (int*)tx->srf->pixels;
		free(str);
	}
}

void	uploading_textures(t_rtv *rtv)
{
	int					i;
	t_mapping_texture	*tx;
	char				*str;

	i = -1;
	while (++i < rtv->figure_num)
		if (rtv->objects[i].texturing == ON &&
				rtv->objects[i].texture.type == MAPPING)
		{
			tx = (t_mapping_texture *)rtv->objects[i].texture.tx_struct;
			str = join("image/", tx->img_path);
			if (!(tx->srf = IMG_Load(str)))
			{
				put_error("Invalid path", str); // при неправильном пути нужно 
				//добавить очистку и выход в меню
				//так как сейчас программа просто аварийно завершается
				// и это плохо

			}
			tx->h = tx->srf->h;
			tx->w = tx->srf->w;
			tx->arr = (int*)tx->srf->pixels;
			free(str);
		}
	uploading_textures_2(rtv, tx);
}

void	free_textures(t_rtv *rtv)
{
	int					i;
	t_mapping_texture	*tx;

	i = -1;
	while (++i < rtv->figure_num)
		if (rtv->objects[i].texturing == ON &&
				rtv->objects[i].texture.type == MAPPING)
		{
			tx = (t_mapping_texture *)rtv->objects[i].texture.tx_struct;
			SDL_FreeSurface(tx->srf);
		}
	if (rtv->sk == ON && rtv->skybox.texturing == ON &&
			rtv->skybox.texture.type == MAPPING)
	{
		tx = (t_mapping_texture *)rtv->skybox.texture.tx_struct;
		SDL_FreeSurface(tx->srf);
	}
}
