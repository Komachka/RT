/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 02:40:58 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/22 22:57:24 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*validate_light_next_2(cJSON *tmp[], t_light *light)
{
	if (validate_vector(tmp[1], &light->pos) ||
		validate_vector(tmp[2], &light->direction))
		return ("Invalid \"Position\" or \"Direction\" value.");
	light->direction = normalize_vector(&light->direction);
	if (validate_color(tmp[3], &light->intensity))
		return ("Invalid \"Intensity\" value.");
	if (tmp[4]->type != cJSON_Number || tmp[4]->valuedouble < 0)
		return ("Invalid \"Constant Attenuation Coefficient\" value.");
	if (tmp[5]->type != cJSON_Number || tmp[5]->valuedouble < 0)
		return ("Invalid \"Linear Attenuation Coefficient\" value.");
	if (tmp[6]->type != cJSON_Number || tmp[6]->valuedouble < 0)
		return ("Invalid \"Quadratic Attenuation Coefficient\" value.");
	light->k_const = tmp[4]->valuedouble;
	light->k_linear = tmp[5]->valuedouble;
	light->k_quadratic = tmp[6]->valuedouble;
	light->epsilon = light->inner_cone - light->outer_cone;
	return (0);
}

char	*validate_light_next(cJSON *obj, cJSON *tmp[], t_light *light)
{
	if (cmp("POINT_LIGHT", tmp[0]->valuestring))
		light->type = POINT_LIGHT;
	else
		light->type = cmp("SPOT_LIGHT", tmp[0]->valuestring) ?
			SPOT_LIGHT : DIRECTIONAL_LIGHT;
	if (light->type == SPOT_LIGHT)
	{
		if (!(tmp[7] = cJSON_GetObjectItemCaseSensitive(obj, "Inner Cone")) ||
			!(tmp[8] = cJSON_GetObjectItemCaseSensitive(obj, "Outer Cone")) ||
			tmp[7]->type != cJSON_Number || tmp[8]->type != cJSON_Number ||
			tmp[7]->valuedouble <= 0 || tmp[7]->valuedouble >= 180.0 ||
			tmp[8]->valuedouble < 0 ||
			(tmp[7]->valuedouble + tmp[8]->valuedouble) > 180.0)
			return ("\"Inner Cone\" or \"Outer Cone\" error.");
	}
	light->inner_cone = (light->type == SPOT_LIGHT) ?
		cos(TO_RAD(tmp[7]->valuedouble) / 2.0) : 0;
	light->outer_cone = (light->type == SPOT_LIGHT) ?
		cos(TO_RAD(((tmp[7]->valuedouble / 2.0) + tmp[8]->valuedouble))) : 0;
	return (validate_light_next_2(tmp, light));
}

char	*validate_light(cJSON *obj, t_rtv *rtv)
{
	cJSON		*tmp[9];
	char		*arr[7];
	char		*str;

	VAR_INT(counter, -1);
	valid_data(arr, "Light");
	rtv->light_num = cJSON_GetArraySize(obj);
	if (!(rtv->l = (t_light *)malloc(sizeof(t_light) * rtv->light_num)))
		malloc_error();
	while (++counter < rtv->light_num)
	{
		VAR_INT(index, -1);
		while (++index < 7)
			if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(
					cJSON_GetArrayItem(obj, counter), arr[index])))
				return (arr[index]);
		if (!cmp("POINT_LIGHT", tmp[0]->valuestring) &&
			!cmp("SPOT_LIGHT", tmp[0]->valuestring) &&
			!cmp("DIRECTIONAL_LIGHT", tmp[0]->valuestring))
			return ("Invalid \"Type\" value.");
		if ((str = validate_light_next(cJSON_GetArrayItem(obj, counter),
										tmp, &rtv->l[counter])))
			return (str);
	}
	return (0);
}
