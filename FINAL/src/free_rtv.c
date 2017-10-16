/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rtv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 04:09:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 13:16:33 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	ft_free2(t_rtv *rtv, t_polygon *p)
{
	p = (t_polygon*)rtv->objects[rtv->figure_num].object;
	free(p->vx);
	free(p->index);
	free(p->col);
	free(p->norm);
}

static inline void	ft_free3(t_rtv *rtv)
{
	t_mapping_texture	*mt;

	if (rtv->skybox.texture.type == MAPPING)
	{
		mt = (t_mapping_texture*)rtv->skybox.texture.tx_struct;
		free(mt->img_path);
	}
	free(rtv->skybox.texture.tx_struct);
}

static inline void	ft_free(t_rtv *rtv)
{
	t_mapping_texture	*mt;

	if (rtv->objects[rtv->figure_num].texture.type == MAPPING)
	{
		mt =
			(t_mapping_texture*)rtv->objects[rtv->figure_num].texture.tx_struct;
		free(mt->img_path);
	}
	free(rtv->objects[rtv->figure_num].texture.tx_struct);
}

void				free_rtv(t_rtv *rtv)
{
	t_plane_with_hole	*pl;
	t_polygon			*p;

	p = 0;
	while (--rtv->figure_num != -1)
	{
		if (rtv->objects[rtv->figure_num].id == PLANE_WITH_HOLE)
		{
			pl = (t_plane_with_hole*)rtv->objects[rtv->figure_num].object;
			free(pl->hole);
		}
		else if (rtv->objects[rtv->figure_num].id == POLYGON)
			ft_free2(rtv, p);
		free(rtv->objects[rtv->figure_num].object);
		if (rtv->objects[rtv->figure_num].texturing == ON)
			ft_free(rtv);
	}
	if (rtv->sk == ON && rtv->skybox.texturing == ON)
		ft_free3(rtv);
	free(rtv->objects);
	free(rtv->l);
}
