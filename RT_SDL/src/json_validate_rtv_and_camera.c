/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_rtv_and_camera.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:23:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 19:20:15 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline char	*validate_rtv_next(cJSON *tmp[], t_rtv *rtv)
{
	cJSON	**obj;
	int		index;

	VAR_INT(arr_size, 0);
	VAR_INT(counter, 5);
	while (++counter < 8)
	{
		index = -1;
		if (tmp[counter]->type != cJSON_Array ||
			!(arr_size = cJSON_GetArraySize(tmp[counter])))
			return (tmp[counter]->string);
		obj = arr_size ? (cJSON**)malloc(sizeof(cJSON*) * arr_size) : 0;
		while (++index < arr_size)
		{
			if (!(obj[index] = cJSON_GetArrayItem(tmp[counter], index)) ||
				obj[index]->type != cJSON_Object)
				return (tmp[counter]->string);
		}
		if (obj)
			free(obj);
	}
	if (validate_color(tmp[4], &rtv->global_light))
		return ("Invalid \"Ambient Light Intensity\" value.");
	return (0);
}

char				*validate_rtv(cJSON *obj, t_rtv *rtv)
{
	cJSON		*tmp[8];
	char		*arr[8];

	VAR_INT(index, -1);
	valid_data(arr, "Rtv");
	while (++index < 8)
		if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(obj, arr[index])))
			return (arr[index]);
	if (!cmp("LAMBERT", tmp[0]->valuestring) &&
		!cmp("CARTOON", tmp[0]->valuestring))
		return ("Invalid \"Light Model\" value.");
	rtv->light_model = cmp("LAMBERT", tmp[0]->valuestring) ? LAMBERT : CARTOON;
	if ((rtv->recursive_depth = tmp[1]->valuedouble) <= 0.0)
		return ("Invalid \"Recursive Depth\" value.");
	if ((rtv->samples_grid = tmp[2]->valuedouble) < 1.0)
		return ("Invalid \"Samples Grid\" value.");
	if (!valid_hex(tmp[3]->valuestring))
		return ("Invalid \"Background Color\" value.");
	rtv->background_color = create_color(tmp[3]->valuestring);
	return (validate_rtv_next(tmp, rtv));
}

static inline char	*validate_camera_2(cJSON *pos, cJSON *rotate, t_camera *cam)
{
	cJSON	*tmp[3];

	VAR_INT(index, -1);
	if (validate_vector(pos, &cam->pos))
		return ("Invalid \"Position\" value.");
	while (++index < 3)
		if (!(tmp[index] = cJSON_GetArrayItem(rotate, index)) ||
			tmp[index]->type != cJSON_Number ||
			cJSON_GetArraySize(rotate) != 3)
			return ("Invalid \"Camera Rotate Angles\" value.");
	cam->rotate[0] = TO_RAD(tmp[0]->valuedouble);
	cam->rotate[1] = TO_RAD(tmp[1]->valuedouble);
	cam->rotate[2] = TO_RAD(tmp[2]->valuedouble);
	cam->image_aspect_ratio = (double)WX / (double)WY;
	cam->lk_dir = 1;
	return (0);
}

char				*validate_camera(cJSON *obj, t_camera *cam)
{
	cJSON		*tmp[5];
	char		*arr[4];

	VAR_INT(index, -1);
	valid_data(arr, "Camera");
	while (++index < 4)
		if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(obj, arr[index])))
			return (arr[index]);
	if (!cmp("STANDART", tmp[0]->valuestring) &&
		!cmp("FISHEYE", tmp[0]->valuestring))
		return ("Invalid \"Light Model\" value.");
	cam->type = cmp("STANDART", tmp[0]->valuestring) ? STANDART : FISHEYE;
	if (cam->type == FISHEYE)
		if (!(tmp[4] = cJSON_GetObjectItem(obj, "Fisheye Angle")) ||
			(tmp[4]->type != cJSON_Number) ||
			(tmp[4]->valuedouble < 0 && tmp[4]->valuedouble > 360.0))
			return ("Fisheye Angle");
	cam->fisheye_angle = cam->type == FISHEYE ? tmp[4]->valuedouble : 0;
	if (tmp[3]->type != cJSON_Number ||
		(tmp[3]->valuedouble < 1.0 && tmp[3]->valuedouble > 180.0))
		return ("Invalid \"FOV\" value.");
	cam->scale = tan(TO_RAD(tmp[3]->valuedouble) / 2);
	if (tmp[2]->type != cJSON_Array || cJSON_GetArraySize(tmp[2]) != 3)
		return ("Invalid \"Camera Rotate Angles\" value.");
	return (validate_camera_2(tmp[1], tmp[2], cam));
}
