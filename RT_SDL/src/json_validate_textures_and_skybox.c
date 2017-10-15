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

static char    *ft_strdup(const char *s1)
{
        char    *s2;
        size_t  i;

        i = 0;
        while (s1[i] != '\0')
                i++;
        if ((s2 = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
                return (NULL);
        i = 0;
        while (s1[i] != '\0')
        {
                s2[i] = s1[i];
                i++;
        }
        s2[i] = '\0';
        return (s2);
}


char	*validate_skybox(cJSON *obj, t_rtv *rtv)
{
	t_figure	temp;
	cJSON		*tmp[2];
	char		*str;

	rtv->sk = OFF;
	if (obj)
	{
		rtv->sk = ON;
		rtv->skybox.pos = rtv->cam.pos;
		if (!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Radius")) ||
		tmp[0]->type != cJSON_Number ||
				(rtv->skybox.r = tmp[0]->valuedouble) <= 0 ||
			!(tmp[1] = cJSON_GetObjectItemCaseSensitive(obj, "Color")) ||
			tmp[1]->type != cJSON_String || !(valid_hex(tmp[1]->valuestring)))
			return ("Invalid Skybox.");
		rtv->skybox.cl = create_color(tmp[1]->valuestring);
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
			!(tmp->valuestring))
		return ("Invalid Mapping \"Texture\"->\"Name\" value.");
	mt->img_path = ft_strdup(tmp->valuestring);
	printf("tmp->valuestring = %s\n", tmp->valuestring);
	if (figure->id == SPHERE)
		figure->texture.creating_texture = &sphere_mapping_texture;
	figure->texture.tx_struct = (void*)mt;
	return (0);
}
