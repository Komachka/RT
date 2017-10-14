/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rtv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 04:09:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/14 04:09:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	free_rtv(t_rtv *rtv)
{
	t_plane_with_hole	*pl;
	t_polygon			*p;
	t_mapping_texture	*mt;

	while (--rtv->figure_num != -1)
	{
		if (rtv->objects[rtv->figure_num].id == PLANE_WITH_HOLE)
		{
			pl = (t_plane_with_hole*)rtv->objects[rtv->figure_num].object;
			free(pl->hole);
		}
		else if (rtv->objects[rtv->figure_num].id == POLYGON)
		{
			p = (t_polygon*)rtv->objects[rtv->figure_num].object;
			free(p->vx);
			free(p->index);
			free(p->col);
			free(p->norm);
		}
		free(rtv->objects[rtv->figure_num].object);
		if (rtv->objects[rtv->figure_num].texturing == ON)
		{
			if (rtv->objects[rtv->figure_num].texture.type == MAPPING)
			{
				mt = (t_mapping_texture*)rtv->objects[rtv->figure_num].texture.tx_struct;
				free(mt->img_path);
			}
			free(rtv->objects[rtv->figure_num].texture.tx_struct); 
		}
	}
	free(rtv->objects);
	free(rtv->l);

}
