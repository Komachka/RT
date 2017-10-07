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

char	*validate_objects_next_2(cJSON *tmp[], cJSON *material[], t_figure *fig)
{
	char	*arr[15];
	int		num[14];

	VAR_INT(index, -1);
	valid_data(arr, "Id");
	valid_id_list(num);
	while (arr[++index])
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
		(fig->material.refraction = material[7]->valuedouble) < 1)
		return ("Invalid \"Refraction\" value.");
	fig->material.texture = 0;
	return (validate_object(tmp[1], fig, fig->id));
}

char	*validate_objects_next(cJSON *tmp[], t_figure *figure)
{
	cJSON	*material[8];
	char	*arr[9];

	VAR_INT(i, -1);
	valid_data(arr, "Material");
	while (arr[++i])
		if (!(material[i] = cJSON_GetObjectItemCaseSensitive(tmp[2], arr[i])))
			return (arr[i]);
	if (!valid_hex(material[0]->valuestring))
		return ("Invalid \"Color\" value.");
	VAR_INT(color, ft_atoi_base(material[0]->valuestring, 16));
	figure->material.cl = (t_color){(unsigned char)(color >> 16) / 255.0,
									(unsigned char)(color >> 8) / 255.0,
									(unsigned char)color / 255.0,
									(unsigned char)(color >> 24) / 100.0};
	if (validate_color(material[1], &figure->material.ambient))
		return ("Invalid \"Ambient\" value.");
	if (validate_color(material[2], &figure->material.diffuse))
		return ("Invalid \"Diffuse\" value.");
	if (validate_color(material[3], &figure->material.specular))
		return ("Invalid \"Specular\" value.");
	return (validate_objects_next_2(tmp, material, figure));
}

char	*validate_object_texture(cJSON *obj, t_figure *figure)
{
	cJSON	*tmp[2];
	char	*arr[1];

	figure->texturing = OFF;
	if ((tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Texture")))
	{
		if (!(tmp[1] = cJSON_GetObjectItemCaseSensitive(tmp[0], "Type")) ||
				(!cmp("MAPPING", tmp[1]->valuestring) &&
			!cmp("PERLIN", tmp[1]->valuestring)))
			return ("Invalid \"Texture\"->\"Type\".");
		figure->texture.type = PERLIN;
		if (cmp("MAPPING", tmp[1]->valuestring))
		{
			valid_data_2(arr, "Textures");
			VAR_INT(i, -1);
			while (++i < (int)(sizeof(arr) / sizeof(char*)))
				if (!cmp(arr[i], tmp[1]->valuestring))
					return ("No MAPPING for figure");
			figure->texture.type = MAPPING;
		}
		figure->texturing = ON;
		return (validate_texture(tmp[0], figure));
	}
	return (0);
}

char	*validate_objects(cJSON *obj, t_rtv *rtv)
{
	cJSON	*tmp[3];
	char	*arr[4];
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
		while (arr[++index])
			if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(
					cJSON_GetArrayItem(obj, counter), arr[index])))
				return (arr[index]);
		rtv->objects[counter].id = -1;
		if ((str = validate_objects_next(tmp, &rtv->objects[counter])) ||
			(str = validate_object_texture(cJSON_GetArrayItem(obj, counter),
									&rtv->objects[counter])))
			return (str);
	}
	return (0);
}
