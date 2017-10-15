/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 02:42:45 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 19:49:51 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline char	*validate_3(cJSON *tmp[], cJSON *material[], t_figure *fig)
{
	char	*arr[16];
	int		num[16];

	VAR_INT(index, -1);
	valid_data(arr, "Id");
	valid_id_list(num);
	while (++index < 16)
		if (cmp(arr[index], tmp[0]->valuestring))
			fig->id = num[index];
	if (fig->id < 0)
		return ("Invalid \"Id\" value.");
	if (material[4]->type != cJSON_Number ||
		(fig->material.shininess = material[4]->valuedouble) < 0)
		return ("Invalid \"Shininess\" value.");
	if (material[5]->type != cJSON_Number || material[5]->valuedouble > 1 ||
		(fig->material.reflective = material[5]->valuedouble) < 0)
		return ("Invalid \"Reflective\" value.");
	if (material[6]->type != cJSON_Number || material[6]->valuedouble > 1 ||
		(fig->material.transparency = material[6]->valuedouble) < 0)
		return ("Invalid \"Transparency\" value.");
	if (material[7]->type != cJSON_Number ||
		(fig->material.refraction = material[7]->valuedouble) < 1 ||
			fig->material.refraction > 1.6)
		return ("Invalid \"Refraction\" value.");
	return (validate_object(tmp[1], fig, fig->id));
}

static inline char	*validate_objects_2(cJSON *tmp[], t_figure *figure)
{
	cJSON	*material[8];
	char	*arr[8];

	VAR_INT(i, -1);
	valid_data(arr, "Material");
	while (++i < 8)
		if (!(material[i] = cJSON_GetObjectItemCaseSensitive(tmp[2], arr[i])))
			return (arr[i]);
	if (!valid_hex(material[0]->valuestring))
		return ("Invalid \"Color\" value.");
	figure->material.cl = create_color(material[0]->valuestring);
	if (validate_color(material[1], &figure->material.ambient))
		return ("Invalid \"Ambient\" value.");
	if (validate_color(material[2], &figure->material.diffuse))
		return ("Invalid \"Diffuse\" value.");
	if (validate_color(material[3], &figure->material.specular))
		return ("Invalid \"Specular\" value.");
	return (validate_3(tmp, material, figure));
}

static inline char	*get_texture_type(char *type, t_figure *figure) ///
{
	int		num[6];
	char	*arr[6];

	VAR_INT(i, -1);
	valid_data_2(arr, "Textures");
	valid_id_list_2(num);
	figure->texture.type = -1;
	while (++i < 6)
		if (cmp(arr[i], type))
			figure->texture.type = num[i];
	if (figure->texture.type < 0)
		return ("Invalid \"Texture\"->\"Type\".");
	if (figure->texture.type == MAPPING && figure->id != SPHERE)
		return ("No MAPPING for figure");
	figure->texturing = ON;
	return (0);
}

char				*validate_object_texture(cJSON *obj, t_figure *figure)
{
	cJSON	*tmp[2];
	char	*str;

	figure->texturing = OFF;
	if ((tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Texture")))
	{
		if (!(tmp[1] = cJSON_GetObjectItemCaseSensitive(tmp[0], "Type")) ||
				!(tmp[1]->valuestring))
			return ("Invalid \"Texture\"->\"Type\".");
		if ((str = get_texture_type(tmp[1]->valuestring, figure)))
			return (str);
		return (validate_texture(tmp[0], figure));
	}
	return (0);
}

char				*validate_objects(cJSON *obj, t_rtv *rtv)
{
	cJSON	*tmp[3];
	char	*arr[3];
	char	*str;

	if (!obj || obj->type != cJSON_Array)
		return ("Invalid Objects Array");
	valid_data(arr, "Objects");
	rtv->figure_num = cJSON_GetArraySize(obj);
	if (!(rtv->objects = (t_figure*)malloc(sizeof(t_figure) * rtv->figure_num)))
		malloc_error();
	VAR_INT(counter, -1);
	while (++counter < rtv->figure_num)
	{
		VAR_INT(index, -1);
		while (++index < 3)
			if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(
					cJSON_GetArrayItem(obj, counter), arr[index])))
				return (arr[index]);
		rtv->objects[counter].id = -1;
		if ((str = validate_objects_2(tmp, &rtv->objects[counter])) ||
			(str = validate_object_texture(cJSON_GetArrayItem(obj, counter),
									&rtv->objects[counter])))
			return (str);
	}
	return (0);
}
