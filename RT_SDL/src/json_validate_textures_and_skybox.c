/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 01:28:35 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 19:37:48 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*validate_skybox(cJSON *obj, t_rtv *rtv)
{
	t_figure	temp;
	cJSON		*tmp;
	char		*str;

	rtv->sk = OFF;
	if (obj)
	{
		rtv->sk = ON;
		rtv->skybox.pos = rtv->cam.pos;
		if (!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Radius")) ||
		tmp->type != cJSON_Number || (rtv->skybox.r = tmp->valuedouble) <= 0 ||
			!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Color")) ||
			tmp->type != cJSON_String || !(valid_hex(tmp->valuestring)))
			return ("Invalid Skybox.");
		rtv->skybox.cl = create_color(tmp->valuestring);
		temp.id = SPHERE;
		if ((str = validate_object_texture(obj, &temp)))
			return (str);
		rtv->skybox.texturing = temp.texturing;
		if (rtv->skybox.texturing == ON)
			rtv->skybox.texture = temp.texture;
	}
	return (0);
}

char	*validate_texture(cJSON *obj, t_figure *figure)
{
	t_mapping_texture	*mt;
	cJSON				*tmp;

	if (figure->texture.type == PERLIN)
		return (validate_perlin(obj, figure));
	if (figure->texture.type == PLASMA)
		return (validate_plasma(obj, figure));
	if (figure->texture.type == CONTOURS)
		return (validate_contours(obj, figure));
	if (figure->texture.type == CAUSTIC)
		return (validate_caustic(obj, figure));
	if (figure->texture.type == JUPITER)
		return (validate_jupiter(obj, figure));
	if (!(mt = (t_mapping_texture*)malloc(sizeof(t_mapping_texture))))
		malloc_error();
	if (!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Path")) ||
			!(mt->img_path = tmp->valuestring))
		return ("Invalid Mapping \"Texture\"->\"Name\" value.");
	if (figure->id == SPHERE)
		figure->texture.creating_texture = &sphere_mapping_texture;
	figure->texture.tx_struct = (void*)mt;
	return (0);
}
