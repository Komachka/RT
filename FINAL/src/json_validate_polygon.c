/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_polygon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 00:05:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/14 00:05:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline char	*vertex_index(cJSON *tmp[], t_polygon *p, int vx_size)
{
	cJSON	*obj;

	!(p->vx = (t_vect*)malloc(sizeof(t_vect) * vx_size)) ? malloc_error() : 0;
	VAR_INT(i, -1);
	while (++i < vx_size)
		if (validate_vector(cJSON_GetArrayItem(tmp[1], i), &p->vx[i]))
			return ("Invalid Polygon \"Vertex\" value.");
	VAR_INT(index_size, 0);
	if (tmp[2]->type != cJSON_Array ||
			(index_size = cJSON_GetArraySize(tmp[2])) != (p->faces * 3))
		return ("Invalid Polygon \"Index\" array.");
	!(p->index = (int*)malloc(sizeof(int) * index_size)) ? malloc_error() : 0;
	i = -1;
	while (++i < index_size)
		if (!(obj = cJSON_GetArrayItem(tmp[2], i)) ||
			obj->type != cJSON_Number ||
			(p->index[i] = obj->valueint) < 0 || p->index[i] >= vx_size)
			return ("Invalid Polygon \"Index\" value.");
	i = p->faces;
	while (--i != -1)
		if (p->index[i * 3] == p->index[i * 3 + 1] ||
			p->index[i * 3] == p->index[i * 3 + 2] ||
			p->index[i * 3 + 1] == p->index[i * 3 + 2])
			return ("Invalid Polygon \"Index\" number.");
	return (0);
}

static inline void	creating_polygon_normals(t_polygon *p)
{
	int			i;
	t_triangle	tr;

	i = 0;
	while (i < p->faces)
	{
		tr.a = p->vx[p->index[i * 3]];
		tr.b = p->vx[p->index[i * 3 + 1]];
		tr.c = p->vx[p->index[i * 3 + 2]];
		tr.v0 = vector_substract(&tr.b, &tr.a);
		tr.v1 = vector_substract(&tr.c, &tr.a);
		p->norm[i] = vector_cross_product(&tr.v0, &tr.v1);
		p->norm[i] = normalize_vector(&p->norm[i]);
		i++;
	}
}

static inline char	*color(cJSON *tmp[], t_polygon *p)
{
	cJSON	*obj;

	if (!(p->col = (t_color*)malloc(sizeof(t_color) * p->faces)))
		malloc_error();
	if (tmp[3]->type != cJSON_Array || cJSON_GetArraySize(tmp[3]) != p->faces)
		return ("Invalid Polygon \"Color\" array.");
	VAR_INT(i, p->faces);
	while (--i != -1)
	{
		if (!(obj = cJSON_GetArrayItem(tmp[3], i)) ||
				!valid_hex(obj->valuestring))
			return ("Invalid Polygon \"Color\" value.");
		p->col[i] = create_color(obj->valuestring);
	}
	return (0);
}

char				*validate_polygon(cJSON *tmp[], t_figure *figure)
{
	t_polygon	*p;
	char		*str;

	VAR_INT(vx_size, 0);
	if (!(p = (t_polygon*)malloc(sizeof(t_polygon))))
		malloc_error();
	if (tmp[0]->type != cJSON_Number || (p->faces = tmp[0]->valueint) < 1)
		return ("Invalid Polygon \"Faces\" value.");
	if (tmp[1]->type != cJSON_Array ||
			(vx_size = cJSON_GetArraySize(tmp[1])) < 3)
		return ("Invalid Polygon \"Vertex\" array.");
	if ((str = vertex_index(tmp, p, vx_size)))
		return (str);
	if (!(p->norm = (t_vect*)malloc(sizeof(t_vect) * p->faces)))
		malloc_error();
	creating_polygon_normals(p);
	if ((str = color(tmp, p)))
		return (str);
	figure->intersection_object = &intersection_polygon;
	figure->norm_vector = &polygon_norm_vector;
	figure->object = (void*)p;
	return (0);
}
