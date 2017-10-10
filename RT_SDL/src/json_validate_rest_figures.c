/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_rest_figures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 22:41:27 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/24 00:12:42 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*validate_holes(cJSON *object, t_plane_with_hole *pl)
{
	cJSON *tmp[3];

	if (!(pl->hole = (t_disc*)malloc(sizeof(t_disc) * pl->holes_num)))
		malloc_error();
	VAR_INT(i, 0);
	while (i < pl->holes_num)
	{
		if (!(tmp[0] = cJSON_GetArrayItem(object, i)) ||
			!(tmp[1] = cJSON_GetObjectItemCaseSensitive(tmp[0], "Position")) ||
			(validate_vector(tmp[1], &pl->hole[i].pos)) ||
			!(tmp[2] = cJSON_GetObjectItemCaseSensitive(tmp[0], "Radius")) ||
			tmp[2]->type != cJSON_Number ||
			(pl->hole[i].r = tmp[2]->valuedouble) <= 0)
			return ("Invalid Plane Plane With Hole \"Holes\" Array.");
		pl->hole[i].pos = project_point_on_plane(&pl->hole[i].pos, &pl->point,
												&pl->norm);
		pl->hole[i].norm = pl->norm;
		i++;
	}
	return (0);
}

char	*validate_plane_with_hole(cJSON *tmp[], t_figure *figure)
{
	t_plane_with_hole	*pl;
	char				*str;

	if (!(pl = (t_plane_with_hole *)malloc(sizeof(t_plane_with_hole))))
		malloc_error();
	if (validate_vector(tmp[0], &pl->norm))
		return ("Invalid Plane With Hole \"Normal Vector\" value.");
	pl->norm = normalize_vector(&pl->norm);
	if (validate_vector(tmp[1], &pl->point))
		return ("Invalid Plane Plane With Hole \"Point On The Plane\" value.");
	if (tmp[2]->type != cJSON_Array ||
			!(pl->holes_num = cJSON_GetArraySize(tmp[2])))
		return ("Invalid Plane Plane With Hole \"Holes\" value.");
	if ((str = validate_holes(tmp[2], pl)))
		return (str);
	figure->intersection_object = &intersection_plane_with_hole;
	figure->norm_vector = &plane_with_hole_norm_vector;
	figure->object = (void *)pl;
	return (0);
}

char	*validate_disc_with_hole(cJSON *obj[], t_figure *figure)
{
	t_disc_with_hole	*dh;
	cJSON				*tmp[3];

	if (!(dh = (t_disc_with_hole*)malloc(sizeof(t_disc_with_hole))))
		malloc_error();
	if (!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj[0], "Position")) ||
		!(tmp[1] = cJSON_GetObjectItemCaseSensitive(obj[0], "Normal Vector")) ||
		!(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj[0], "Radius")) ||
		validate_vector(tmp[0], &dh->disc.pos) ||
		validate_vector(tmp[1], &dh->disc.norm) ||
	tmp[2]->type != cJSON_Number || (dh->disc.r = tmp[2]->valuedouble) <= 0 ||
		!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj[1], "Position")) ||
		!(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj[1], "Radius")) ||
		validate_vector(tmp[0], &dh->hole.pos) ||
	tmp[2]->type != cJSON_Number || (dh->hole.r = tmp[2]->valuedouble) <= 0 ||
			dh->hole.r > dh->disc.r)
		return ("Invalid Disc With Hole.");
	dh->disc.norm = normalize_vector(&dh->disc.norm);
	dh->hole.norm = dh->disc.norm;
	dh->hole.pos = project_point_on_plane(&dh->hole.pos, &dh->disc.pos,
										&dh->disc.norm);
	figure->intersection_object = &intersection_disc_with_hole;
	figure->norm_vector = &disc_with_hole_norm_vector;
	figure->object = (void*)dh;
	return (0);
}
