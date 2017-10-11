/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_vector_and_color.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:20:49 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 20:32:05 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

_Bool	validate_color(cJSON *obj, t_color *color)
{
	cJSON	*tmp[4];
	char	*arr[5];

	arr[0] = "Red";
	arr[1] = "Green";
	arr[2] = "Blue";
	arr[3] = "Alpha";
	VAR_INT(index, -1);
	while (++index < 4)
		if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(obj, arr[index])) ||
			tmp[index]->type != cJSON_Number || tmp[index]->valuedouble < 0 ||
			tmp[index]->valuedouble > 1)
			return (1);
	color->r = tmp[0]->valuedouble;
	color->g = tmp[1]->valuedouble;
	color->b = tmp[2]->valuedouble;
	color->al = tmp[3]->valuedouble;
	return (0);
}

_Bool	validate_vector(cJSON *obj, t_vect *vect)
{
	cJSON	*tmp[3];
	char	*arr[4];

	arr[0] = "x";
	arr[1] = "y";
	arr[2] = "z";
	VAR_INT(index, -1);
	while (++index < 3)
		if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(obj, arr[index])) ||
			tmp[index]->type != cJSON_Number)
			return (1);
	vect->x = tmp[0]->valuedouble;
	vect->y = tmp[1]->valuedouble;
	vect->z = tmp[2]->valuedouble;
	return (0);
}
