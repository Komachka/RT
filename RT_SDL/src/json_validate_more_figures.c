/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_more_figures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 21:57:29 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/24 00:20:02 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*validate_triangle(cJSON *tmp[], t_figure *figure)
{
	t_triangle *triangle;

	if (!(triangle = (t_triangle*)malloc(sizeof(t_triangle))))
		malloc_error();
	if (validate_vector(tmp[0], &triangle->a))
		return ("Invalid Triangle \"Vertex A\" value.");
	if (validate_vector(tmp[1], &triangle->b))
		return ("Invalid Triangle \"Vertex B\" value.");
	if (validate_vector(tmp[2], &triangle->c))
		return ("Invalid Triangle \"Vertex C\" value.");
	triangle->v0 = vector_substract(&triangle->b, &triangle->a);
	triangle->v1 = vector_substract(&triangle->c, &triangle->a);
	triangle->norm = vector_cross_product(&triangle->v0, &triangle->v1);
	triangle->norm = normalize_vector(&triangle->norm);
	figure->intersection_object = &intersection_triangle;
	figure->norm_vector = &triangle_norm_vector;
	figure->object = (void*)triangle;
	return (0);
}

char	*validate_disc(cJSON *tmp[], t_figure *figure)
{
	t_disс *disc;

	if (!(disc = (t_disс*)malloc(sizeof(t_disс))))
		malloc_error();
	if (validate_vector(tmp[0], &disc->pos))
		return ("Invalid Disc \"Position\" value.");
	if (validate_vector(tmp[1], &disc->norm))
		return ("Invalid Disc \"Normal Vector\" value.");
	disc->norm = normalize_vector(&disc->norm);
	if (tmp[2]->type != cJSON_Number ||
		(disc->r = tmp[2]->valuedouble) <= 0)
		return ("Invalid Disc \"Radius\" value.");
	figure->intersection_object = &intersection_disc;
	figure->norm_vector = &disс_norm_vector;
	figure->object = (void*)disc;
	return (0);
}

char	*validate_ellipsoid(cJSON *tmp[], t_figure *figure)
{
	t_ellipsoid *ellipsoid;

	if (!(ellipsoid = (t_ellipsoid*)malloc(sizeof(t_ellipsoid))))
		malloc_error();
	if (validate_vector(tmp[0], &ellipsoid->pos))
		return ("Invalid Ellipsoid \"Position\" value.");
	if (tmp[1]->type != cJSON_Number ||
		(ellipsoid->size_x = tmp[1]->valuedouble) <= 0)
		return ("Invalid Ellipsoid \"Size x\" value.");
	if (tmp[2]->type != cJSON_Number ||
		(ellipsoid->size_y = tmp[2]->valuedouble) <= 0)
		return ("Invalid Ellipsoid \"Size y\" value.");
	if (tmp[3]->type != cJSON_Number ||
		(ellipsoid->size_z = tmp[3]->valuedouble) <= 0)
		return ("Invalid Ellipsoid \"Size z\" value.");
	figure->intersection_object = &intersection_ellipsoid;
	figure->norm_vector = &ellipsoid_norm_vector;
	figure->object = (void*)ellipsoid;
	return (0);
}

char	*validate_paraboloid(cJSON *tmp[], t_figure *figure)
{
	t_paraboloid *paraboloid;

	if (!(paraboloid = (t_paraboloid*)malloc(sizeof(t_paraboloid))))
		malloc_error();
	if (validate_vector(tmp[0], &paraboloid->extremum))
		return ("Invalid Paraboloid \"Extremum\" value.");
	if (validate_vector(tmp[1], &paraboloid->dir))
		return ("Invalid Paraboloid \"Direction\" value.");
	paraboloid->dir = normalize_vector(&paraboloid->dir);
	if (tmp[2]->type != cJSON_Number ||
		(paraboloid->k = tmp[2]->valuedouble) <= 0)
		return ("Invalid Paraboloid \"Distance\" value.");
	figure->intersection_object = &intersection_paraboloid;
	figure->norm_vector = &paraboloid_norm_vector;
	figure->object = (void*)paraboloid;
	return (0);
}

char	*validate_limited_cylinder(cJSON *tmp[], t_figure *figure)
{
	t_limited_cylinder *lcy;

	if (!(lcy = (t_limited_cylinder*)malloc(sizeof(t_limited_cylinder))))
		malloc_error();
	if (validate_vector(tmp[0], &lcy->p1))
		return ("Invalid Limited Cylinder \"Extremum\" value.");
	if (validate_vector(tmp[1], &lcy->dir))
		return ("Invalid Limited Cylinder \"Direction\" value.");
	lcy->dir = normalize_vector(&lcy->dir);
	if (tmp[2]->type != cJSON_Number || (lcy->r = tmp[2]->valuedouble) <= 0)
		return ("Invalid Limited Cylinder \"Radius\" value.");
	if (tmp[3]->type != cJSON_Number || (lcy->h = tmp[3]->valuedouble) <= 0)
		return ("Invalid Limited Cylinder \"Cut\" value.");
	if (!cmp("ON", tmp[4]->valuestring) && !cmp("OFF", tmp[4]->valuestring))
		return ("Invalid Limited Cylinder \"Caps\" value.");
	lcy->caps = cmp("ON", tmp[4]->valuestring) ? ON : OFF;
	lcy->p2 = vector_mult(lcy->h, &lcy->dir);
	lcy->p2 = vector_add(&lcy->p1, &lcy->p2);
	lcy->p1_norm = change_vector_direction(&lcy->dir);
	lcy->p2_norm = lcy->dir;
	figure->intersection_object = &intersection_limited_cylinder;
	figure->norm_vector = &limited_cylinder_norm_vector;
	figure->object = (void*)lcy;
	return (0);
}
