/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hooks_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:38:38 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:30:13 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	key_funct_8(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_KP_6)
	{
		rtv->cam.pos.x -= 5;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_KP_4)
	{
		rtv->cam.pos.x += 5;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_KP_2)
	{
		rtv->cam.pos.y += 5;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_KP_8)
	{
		rtv->cam.pos.y -= 5;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_s)
	{
		ft_take_picture(rtv);
	}
}

static inline void	key_funct_7(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_BACKSPACE)
	{
		rtv->filter.romanets = 0;
		rtv->filter.black_and_white = 0;
		rtv->filter.blur = 0;
		rtv->filter.glass = 0;
		rtv->filter.emboss = 0;
		rtv->filter.sepia = 0;
		rtv->filter.negative = 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_l)
	{
		rtv->delphin = rtv->delphin == 0 ? 1 : 0;
		ft_redraw(rtv);
	}
	key_funct_8(rtv);
}

static inline void	key_funct_6(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_j)
	{
		if (rtv->filter.sepia == 0)
			rtv->filter.sepia = 1;
		else
			rtv->filter.sepia = 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_n)
	{
		if (rtv->filter.negative == 0)
			rtv->filter.negative = 1;
		else
			rtv->filter.negative = 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_o)
	{
		if (rtv->filter.romanets == 0)
			rtv->filter.romanets = 1;
		else
			rtv->filter.romanets = 0;
		ft_redraw(rtv);
	}
	key_funct_7(rtv);
}

void				key_funct_5(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_u)
	{
		if (rtv->filter.blur == 0)
			rtv->filter.blur = 1;
		else
			rtv->filter.blur = 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_g)
	{
		if (rtv->filter.glass == 0)
			rtv->filter.glass = 1;
		else
			rtv->filter.glass = 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_h)
	{
		if (rtv->filter.emboss == 0)
			rtv->filter.emboss = 1;
		else
			rtv->filter.emboss = 0;
		ft_redraw(rtv);
	}
	key_funct_6(rtv);
}
