/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hooks_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:38:38 by askochul          #+#    #+#             */
/*   Updated: 2017/10/11 22:02:18 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	key_funct_4(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_e)
	{
		rtv->expos -= 0.5;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_r)
	{
		rtv->expos = (rtv->expos <= -0.5) ? (rtv->expos + 0.5) : rtv->expos;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_m)
	{
		if (rtv->filter.black_and_white == 0)
			rtv->filter.black_and_white = 1;
		else
			rtv->filter.black_and_white = 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_p)
	{
		rtv->cam.pos = rtv->def_cam_pos;
		ft_redraw(rtv);
	}
	key_funct_5(rtv);
}

static inline void	key_funct_3(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_KP_PLUS && rtv->light_model == LAMBERT)
	{
		rtv->global_light = calculate_color(1.2, &rtv->global_light);
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_KP_MINUS\
			&& rtv->light_model == LAMBERT)
	{
		rtv->global_light = calculate_color(0.8, \
			&rtv->global_light);
		ft_redraw(rtv);
	}
	if (rtv->e.key.keysym.sym == SDLK_1)
	{
		rtv->light_model = LAMBERT;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_2)
	{
		rtv->light_model = CARTOON;
		ft_redraw(rtv);
	}
	key_funct_4(rtv);
}

static inline void	key_funct_2(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_SPACE)
	{
		rtv->lightening = rtv->lightening == 0 ? 1 : 0;
		rtv->samples = rtv->lightening == ON ? rtv->samples_per_pixel : 1;
		ft_redraw(rtv);
	}
	if (rtv->e.key.keysym.sym == SDLK_b)
	{
		rtv->bg_color = rtv->bg_color == 0 ? 1 : 0;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_EQUALS)
	{
		rtv->cam.pos.z += 5;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_MINUS)
	{
		rtv->cam.pos.z -= 5;
		ft_redraw(rtv);
	}
	key_funct_3(rtv);
}

static inline void	key_funct_1(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_RIGHT)
	{
		rtv->cam.rotate[Y] -= 0.1;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_LEFT)
	{
		rtv->cam.rotate[Y] += 0.1;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_END)
	{
		rtv->cam.rotate[Z] += 0.1;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_HOME)
	{
		rtv->cam.rotate[Z] -= 0.1;
		ft_redraw(rtv);
	}
	key_funct_2(rtv);
}

int					my_key_funct(t_rtv *rtv)
{
	if (rtv->e.key.keysym.sym == SDLK_DOWN)
	{
		rtv->cam.rotate[X] += 0.1;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_UP)
	{
		rtv->cam.rotate[X] -= 0.1;
		ft_redraw(rtv);
	}
	else if (rtv->e.key.keysym.sym == SDLK_q)
	{
		rtv->cam.rotate[X] = rtv->def_cam_dir[X];
		rtv->cam.rotate[Y] = rtv->def_cam_dir[Y];
		rtv->cam.rotate[Z] = rtv->def_cam_dir[Z];
		ft_redraw(rtv);
	}
	key_funct_1(rtv);
	return (0);
}
