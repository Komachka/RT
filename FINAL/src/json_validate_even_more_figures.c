/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_even_more_figures.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 22:41:27 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/24 00:12:42 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline void	validate_limited_cone_2(t_figure *fig, t_limited_cone *lco)
{
	lco->p1 = vector_mult(lco->h1, &lco->dir);
	lco->r1 = vector_length(&lco->p1) * tan(lco->rad);
	lco->p1 = vector_add(&lco->pos, &lco->p1);
	lco->p1_norm = lco->h1 > 0 ? change_vector_direction(&lco->dir) : lco->dir;
	lco->p2 = vector_mult(lco->h2, &lco->dir);
	lco->r2 = vector_length(&lco->p2) * tan(lco->rad);
	lco->p2 = vector_add(&lco->pos, &lco->p2);
	lco->p2_norm = lco->h2 > 0 ? change_vector_direction(&lco->dir) : lco->dir;
	fig->intersection_object = &intersection_limited_cone;
	fig->norm_vector = &limited_cone_norm_vector;
	fig->object = (void*)lco;
}

char				*validate_limited_cone(cJSON *tmp[], t_figure *figure)
{
	t_limited_cone *lco;

	if (!(lco = (t_limited_cone*)malloc(sizeof(t_limited_cone))))
		malloc_error();
	if (validate_vector(tmp[0], &lco->pos))
		return ("Invalid Limited Cone \"Position\" value.");
	if (validate_vector(tmp[1], &lco->dir))
		return ("Invalid Limited Cone \"Direction\" value.");
	lco->dir = normalize_vector(&lco->dir);
	if (tmp[2]->type != cJSON_Number ||
		tmp[2]->valuedouble < 0 || tmp[2]->valuedouble > 180)
		return ("Invalid Limited Cone \"Angle\" value.");
	lco->rad = TO_RAD(tmp[2]->valuedouble);
	if (!cmp("ON", tmp[5]->valuestring) && !cmp("OFF", tmp[5]->valuestring))
		return ("Invalid Limited Cone \"Caps\" value.");
	lco->caps = cmp("ON", tmp[5]->valuestring) ? ON : OFF;
	if (tmp[3]->type != cJSON_Number || tmp[4]->type != cJSON_Number)
		return ("Invalid Limited Cone \"Cut\" value.");
	lco->h1 = tmp[3]->valuedouble;
	lco->h2 = tmp[4]->valuedouble;
	validate_limited_cone_2(figure, lco);
	return (0);
}

char				*validate_limited_paraboloid(cJSON *tmp[], t_figure *figure)
{
	t_limited_paraboloid *lp;

	if (!(lp = (t_limited_paraboloid*)malloc(sizeof(t_limited_paraboloid))))
		malloc_error();
	if (validate_vector(tmp[0], &lp->extremum))
		return ("Invalid Limited Paraboloid \"Extremum\" value.");
	if (validate_vector(tmp[1], &lp->dir))
		return ("Invalid Limited Paraboloid \"Direction\" value.");
	lp->dir = normalize_vector(&lp->dir);
	if (tmp[2]->type != cJSON_Number || (lp->k = tmp[2]->valuedouble) <= 0)
		return ("Invalid Limited Paraboloid \"Distance\" value.");
	if (tmp[3]->type != cJSON_Number || tmp[3]->valuedouble <= 0)
		return ("Invalid Limited Paraboloid \"Cut\" value.");
	lp->bottom = vector_mult(tmp[3]->valuedouble, &lp->dir);
	lp->bottom = vector_add(&lp->extremum, &lp->bottom);
	figure->intersection_object = &intersection_limited_paraboloid;
	figure->norm_vector = &limited_paraboloid_norm_vector;
	figure->object = (void*)lp;
	return (0);
}

static inline void	valid_ls(double cut, t_figure *figure, t_limited_sphere *ls)
{
	ls->cut_r = sqrt((ls->r * ls->r) - (cut * cut));
	ls->p1 = vector_mult(cut, &ls->cut_dir);
	ls->p1 = vector_add(&ls->pos, &ls->p1);
	ls->p2 = vector_mult(-ls->r, &ls->cut_dir);
	ls->p2 = vector_add(&ls->pos, &ls->p2);
	figure->intersection_object = &intersection_limited_sphere;
	figure->norm_vector = &limited_sphere_norm_vector;
	figure->object = (void*)ls;
}

char				*validate_limited_sphere(cJSON *tmp[], t_figure *figure)
{
	t_limited_sphere *ls;

	if (!(ls = (t_limited_sphere*)malloc(sizeof(t_limited_sphere))))
		malloc_error();
	if (validate_vector(tmp[0], &ls->pos))
		return ("Invalid Limited Sphere \"Position\" value.");
	if (validate_vector(tmp[1], &ls->cut_dir))
		return ("Invalid Limited Sphere \"Direction\" value.");
	ls->cut_dir = normalize_vector(&ls->cut_dir);
	if (tmp[2]->type != cJSON_Number || (ls->r = tmp[2]->valuedouble) <= 0)
		return ("Invalid Limited Sphere \"Radius\" value.");
	if (tmp[3]->type != cJSON_Number ||
		tmp[3]->valuedouble > ls->r || tmp[3]->valuedouble < -ls->r)
		return ("Invalid Limited Sphere \"Cut\" value.");
	if (!cmp("ON", tmp[4]->valuestring) && !cmp("OFF", tmp[4]->valuestring))
		return ("Invalid Limited Sphere \"Caps\" value.");
	ls->caps = cmp("ON", tmp[4]->valuestring) ? ON : OFF;
	valid_ls(tmp[3]->valuedouble, figure, ls);
	return (0);
}
