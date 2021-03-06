/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 16:21:18 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 22:38:32 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline char	*validate_object_3(cJSON *object, t_figure *figure, int id)
{
	cJSON *tmp[4];

	if (id == DISC_WITH_HOLE &&
			(tmp[0] = cJSON_GetObjectItemCaseSensitive(object, "Disc")) &&
			(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Hole")))
		return (validate_disc_with_hole(tmp, figure));
	if ((tmp[0] = cJSON_GetObjectItemCaseSensitive(object, "Normal Vector")) &&
	(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Point On The Plane")))
	{
		if (id == PLANE)
			return (validate_plane(tmp, figure));
		if ((tmp[2] = cJSON_GetObjectItemCaseSensitive(object, "Holes")))
			return (validate_plane_with_hole(tmp, figure));
	}
	if (id == POLYGON &&
		(tmp[0] = cJSON_GetObjectItemCaseSensitive(object, "Faces")) &&
		(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Vertex")) &&
		(tmp[2] = cJSON_GetObjectItemCaseSensitive(object, "Index")) &&
		(tmp[3] = cJSON_GetObjectItemCaseSensitive(object, "Color")))
		return (validate_polygon(tmp, figure));
	return ("Some Object Error");
}

static inline char	*validate_object_2(cJSON *object, t_figure *figure, int id)
{
	cJSON *tmp[4];

	if (id == PLANE || id == PLANE_WITH_HOLE || id == DISC_WITH_HOLE ||
		id == POLYGON)
		return (validate_object_3(object, figure, id));
	if (id == TRIANGLE &&
		(tmp[0] = cJSON_GetObjectItemCaseSensitive(object, "Vertex A")) &&
		(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Vertex B")) &&
		(tmp[2] = cJSON_GetObjectItemCaseSensitive(object, "Vertex C")))
		return (validate_triangle(tmp, figure));
	if ((id == PARABOLOID || id == LIMITED_PARABOLOID) &&
		(tmp[0] = cJSON_GetObjectItemCaseSensitive(object, "Extremum")) &&
		(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Direction")) &&
		(tmp[2] = cJSON_GetObjectItemCaseSensitive(object, "Distance")))
	{
		if (id == PARABOLOID)
			return (validate_paraboloid(tmp, figure));
		if ((tmp[3] = cJSON_GetObjectItemCaseSensitive(object, "Cut")))
			return (validate_limited_paraboloid(tmp, figure));
	}
	return ("Some Object Error");
}

static inline char	*valid_2(cJSON *tmp[], cJSON *obj, t_figure *figure, int id)
{
	if (id == CYLINDER && (tmp[2] = cJSON_GetObjectItem(obj, "Radius")))
		return (validate_cylinder(tmp, figure));
	if (id == CONE && (tmp[2] = cJSON_GetObjectItem(obj, "Angle")))
		return (validate_cone(tmp, figure));
	if (id == TORUS && (tmp[2] = cJSON_GetObjectItem(obj, "Minor Radius")) &&
		(tmp[3] = cJSON_GetObjectItemCaseSensitive(obj, "Major Radius")))
		return (validate_torus(tmp, figure));
	if ((id == LIMITED_CONE) &&
		(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj, "Angle")) &&
		(tmp[3] = cJSON_GetObjectItemCaseSensitive(obj, "Cut 1")) &&
		(tmp[4] = cJSON_GetObjectItemCaseSensitive(obj, "Cut 2")) &&
		(tmp[5] = cJSON_GetObjectItemCaseSensitive(obj, "Caps")))
		return (validate_limited_cone(tmp, figure));
	if ((id == LIMITED_CYLINDER || id == LIMITED_SPHERE) &&
		(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj, "Radius")) &&
		(tmp[3] = cJSON_GetObjectItemCaseSensitive(obj, "Cut")) &&
		(tmp[4] = cJSON_GetObjectItemCaseSensitive(obj, "Caps")))
	{
		return ((id == LIMITED_CYLINDER ? validate_limited_cylinder :
				validate_limited_sphere)(tmp, figure));
	}
	return ("Some Object Error");
}

char				*validate_object(cJSON *object, t_figure *figure, int id)
{
	cJSON *tmp[6];

	if ((id == SPHERE || id == CYLINDER || id == CONE || id == TORUS ||
		id == DISC || id == ELLIPSOID || id == LIMITED_CYLINDER ||
		id == LIMITED_CONE || id == LIMITED_SPHERE) &&
		(tmp[0] = cJSON_GetObjectItemCaseSensitive(object, "Position")))
	{
		if (id == SPHERE && (tmp[1] = cJSON_GetObjectItem(object, "Radius")))
			return (validate_sphere(tmp, figure));
		if ((id == CYLINDER || id == LIMITED_CYLINDER || id == CONE ||
			id == LIMITED_CONE || id == LIMITED_SPHERE || id == TORUS) &&
			(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Direction")))
			return (valid_2(tmp, object, figure, id));
		if (id == DISC &&
	(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Normal Vector")) &&
			(tmp[2] = cJSON_GetObjectItemCaseSensitive(object, "Radius")))
			return (validate_disc(tmp, figure));
		if (id == ELLIPSOID &&
			(tmp[1] = cJSON_GetObjectItemCaseSensitive(object, "Size x")) &&
			(tmp[2] = cJSON_GetObjectItemCaseSensitive(object, "Size y")) &&
			(tmp[3] = cJSON_GetObjectItemCaseSensitive(object, "Size z")))
			return (validate_ellipsoid(tmp, figure));
	}
	return (validate_object_2(object, figure, id));
}
