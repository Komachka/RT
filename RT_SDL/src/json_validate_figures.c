/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_figures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 16:28:30 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 19:30:45 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*validate_plane(cJSON *tmp[], t_figure *figure)
{
	t_plane *plane;

	if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
		malloc_error();
	if (validate_vector(tmp[0], &plane->norm))
		return ("Invalid Plane \"Normal Vector\" value.");
	plane->norm = normalize_vector(&plane->norm);
	if (validate_vector(tmp[1], &plane->point))
		return ("Invalid Plane \"Point On The Plane\" value.");
	figure->intersection_object = &intersection_plane;
	figure->norm_vector = &plane_norm_vector;
	figure->object = (void*)plane;
	return (0);
}

char	*validate_torus(cJSON *tmp[], t_figure *figure)
{
	t_torus *torus;

	if (!(torus = (t_torus*)malloc(sizeof(t_torus))))
		malloc_error();
	if (validate_vector(tmp[0], &torus->pos))
		return ("Invalid Torus \"Position\" value.");
	if (validate_vector(tmp[1], &torus->dir))
		return ("Invalid Torus \"Direction\" value.");
	torus->dir = normalize_vector(&torus->dir);
	if (tmp[2]->type != cJSON_Number ||
		(torus->min_r = tmp[2]->valuedouble) <= 0)
		return ("Invalid Torus \"Minor Radius\" value.");
	if (tmp[3]->type != cJSON_Number ||
		(torus->maj_r = tmp[3]->valuedouble) < torus->min_r)
		return ("Invalid Torus \"Major Radius\" value.");
	figure->intersection_object = &intersection_torus;
	figure->norm_vector = &torus_norm_vector;
	figure->object = (void*)torus;
	return (0);
}

char	*validate_cone(cJSON *tmp[], t_figure *figure)
{
	t_cone *cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		malloc_error();
	if (validate_vector(tmp[0], &cone->pos))
		return ("Invalid Cone \"Position\" value.");
	if (validate_vector(tmp[1], &cone->dir))
		return ("Invalid Cone \"Direction\" value.");
	cone->dir = normalize_vector(&cone->dir);
	if (tmp[2]->type != cJSON_Number ||
		(cone->rad = tmp[2]->valuedouble) <= 0)
		return ("Invalid Cone \"Angle\" value.");
	cone->rad = TO_RAD(cone->rad);
	figure->intersection_object = &intersection_cone;
	figure->norm_vector = &cone_norm_vector;
	figure->object = (void*)cone;
	return (0);
}

char	*validate_cylinder(cJSON *tmp[], t_figure *figure)
{
	t_cylinder *cylinder;

	if (!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		malloc_error();
	if (validate_vector(tmp[0], &cylinder->pos))
		return ("Invalid Cylinder \"Position\" value.");
	if (validate_vector(tmp[1], &cylinder->dir))
		return ("Invalid Cylinder \"Direction\" value.");
	cylinder->dir = normalize_vector(&cylinder->dir);
	if (tmp[2]->type != cJSON_Number ||
		(cylinder->r = tmp[2]->valuedouble) <= 0)
		return ("Invalid Cylinder \"Radius\" value.");
	figure->intersection_object = &intersection_cylinder;
	figure->norm_vector = &cylinder_norm_vector;
	figure->object = (void*)cylinder;
	return (0);
}

char	*validate_sphere(cJSON *tmp[], t_figure *figure)
{
	t_sphere *sphere;

	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		malloc_error();
	if (validate_vector(tmp[0], &sphere->pos))
		return ("Invalid Sphere \"Position\" value.");
	if (tmp[1]->type != cJSON_Number || (sphere->r = tmp[1]->valuedouble) <= 0)
		return ("Invalid Sphere \"Radius\" value.");
	figure->intersection_object = &intersection_sphere;
	figure->norm_vector = &sphere_norm_vector;
	figure->object = (void*)sphere;
	return (0);
}
