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

char	*validate_perlin(cJSON *obj, t_figure *figure)
{
	t_perlin_texture	*pr;
	cJSON				*tmp;

	if (!(pr = (t_perlin_texture*)malloc(sizeof(t_perlin_texture))))
		malloc_error();
	if (!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Octaves")) ||
			(pr->octaves = tmp->valuedouble) <= 1 ||
			!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Amplitude")) ||
			(pr->amplitude = tmp->valuedouble) <= 0 ||
			!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Persistence")) ||
			(pr->persistence = tmp->valuedouble) <= 0 ||
			!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Exponent")) ||
			(pr->exponent = tmp->valuedouble) <= 0 ||
			!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Frequency")) ||
			validate_vector(tmp, &pr->frequency) ||
			!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Frequency Att")) ||
			validate_vector(tmp, &pr->frequency_att))
		return ("Invalid one of \"Texture\" values.");
	figure->texture.creating_texture = &perlin_noise_texture;
	figure->texture.tx_struct = (void*)pr;
	return (0);
}

char	*validate_texture(cJSON *obj, t_figure *figure)
{
	t_mapping_texture	*mt;
	cJSON				*tmp;

	if (figure->texture.type == PERLIN)
		return (validate_perlin(obj, figure));
	if (!(mt = (t_mapping_texture*)malloc(sizeof(t_mapping_texture))))
		malloc_error();
	if (!(tmp = cJSON_GetObjectItemCaseSensitive(obj, "Path")) ||
			!(mt->img_path = tmp->valuestring))
		return ("Invalid \"Texture\"->\"Name\" value.");
	if (figure->id == SPHERE)
		figure->texture.creating_texture = &sphere_mapping_texture;
	figure->texture.tx_struct = (void*)mt;
	return (0);
}
