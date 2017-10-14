/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_validate_procedural_textures.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 23:17:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/08 23:17:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*validate_perlin(cJSON *obj, t_figure *figure)
{
	t_perlin_texture	*pr;
	cJSON				*tmp[6];

	if (!(pr = (t_perlin_texture*)malloc(sizeof(t_perlin_texture))))
		malloc_error();
	if (!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Octaves")) ||
		(pr->octaves = tmp[0]->valuedouble) <= 1 ||
		!(tmp[1] = cJSON_GetObjectItemCaseSensitive(obj, "Amplitude")) ||
		(pr->amplitude = tmp[1]->valuedouble) <= 0 ||
		!(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj, "Persistence")) ||
		(pr->persistence = tmp[2]->valuedouble) <= 0 ||
		!(tmp[3] = cJSON_GetObjectItemCaseSensitive(obj, "Exponent")) ||
		(pr->exponent = tmp[3]->valuedouble) <= 0 ||
		!(tmp[4] = cJSON_GetObjectItemCaseSensitive(obj, "Frequency")) ||
		validate_vector(tmp[4], &pr->frequency) ||
		!(tmp[5] = cJSON_GetObjectItemCaseSensitive(obj, "Frequency Att")) ||
		validate_vector(tmp[5], &pr->frequency_att))
		return ("Invalid Perlin Texture.");
	figure->texture.creating_texture = &perlin_noise_texture;
	figure->texture.tx_struct = (void*)pr;
	return (0);
}

char	*validate_plasma(cJSON *obj, t_figure *figure)
{
	t_plasma_texture	*pl;
	cJSON				*tmp[2];

	if (!(pl = (t_plasma_texture*)malloc(sizeof(t_plasma_texture))))
		malloc_error();
	if (!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Frequency")) ||
			valid_color(tmp[0], &pl->frequency) ||
			!(tmp[1] = cJSON_GetObjectItemCaseSensitive(obj, "Phase")) ||
			valid_color(tmp[1], &pl->phase))
		return ("Invalid Plasma Texture.");
	figure->texture.tx_struct = (void*)pl;
	figure->texture.creating_texture = &plasma_texture;
	return (0);
}

char	*validate_contours(cJSON *obj, t_figure *figure)
{
	t_contours_texture	*ct;
	cJSON				*tmp[4];

	if (!(ct = (t_contours_texture*)malloc(sizeof(t_contours_texture))))
		malloc_error();
	if (!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Contour")) ||
		!(tmp[1] = cJSON_GetObjectItemCaseSensitive(obj, "Background")) ||
		!(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj, "Thickness")) ||
		!(tmp[3] = cJSON_GetObjectItemCaseSensitive(obj, "Frequency")) ||
		tmp[0]->type != cJSON_String || tmp[1]->type != cJSON_String ||
		tmp[2]->type != cJSON_Number || tmp[3]->type != cJSON_Number ||
		tmp[2]->valuedouble < 0 || tmp[2]->valuedouble > 1 ||
		tmp[3]->valuedouble <= 0 || !(valid_hex(tmp[0]->valuestring)) ||
		!(valid_hex(tmp[1]->valuestring)))
		return ("Invalid Contours Texture");
	ct->contour = create_color(tmp[0]->valuestring);
	ct->background = create_color(tmp[1]->valuestring);
	ct->t = tmp[2]->valuedouble;
	ct->frequency = tmp[3]->valuedouble;
	figure->texture.tx_struct = (void*)ct;
	figure->texture.creating_texture = &contours_texture;
	return (0);
}

char	*validate_caustic(cJSON *obj, t_figure *figure)
{
	t_caustic_texture	*ct;
	cJSON				*tmp[4];

	if (!(ct = (t_caustic_texture*)malloc(sizeof(t_caustic_texture))))
		malloc_error();
	if (!(tmp[0] = cJSON_GetObjectItemCaseSensitive(obj, "Color 1")) ||
		!(tmp[1] = cJSON_GetObjectItemCaseSensitive(obj, "Color 2")) ||
		!(tmp[2] = cJSON_GetObjectItemCaseSensitive(obj, "Sharpness")) ||
		!(tmp[3] = cJSON_GetObjectItemCaseSensitive(obj, "Coverage")) ||
		tmp[0]->type != cJSON_String || tmp[1]->type != cJSON_String ||
		tmp[2]->type != cJSON_Number || tmp[3]->type != cJSON_Number ||
		tmp[2]->valuedouble < 0 || tmp[2]->valuedouble > 1 ||
		tmp[3]->valuedouble < 0 || tmp[3]->valuedouble > 1 ||
		!(valid_hex(tmp[0]->valuestring)) || !(valid_hex(tmp[1]->valuestring)))
		return ("Invalid Caustic Texture");
	ct->color_1 = create_color(tmp[0]->valuestring);
	ct->color_2 = create_color(tmp[1]->valuestring);
	ct->sharpness = tmp[2]->valuedouble;
	ct->coverage = tmp[3]->valuedouble;
	figure->texture.tx_struct = (void*)ct;
	figure->texture.creating_texture = &caustic_texture;
	return (0);
}

char	*validate_jupiter(cJSON *obj, t_figure *figure)
{
	t_jupiter_texture	*jt;
	cJSON				*tmp[6];
	char				*arr[6];

	if (!(jt = (t_jupiter_texture*)malloc(sizeof(t_jupiter_texture))))
		malloc_error();
	VAR_INT(i, -1);
	valid_data_2(arr, "Jupiter");
	while (++i < 6)
		if (!(tmp[i] = cJSON_GetObjectItemCaseSensitive(obj, arr[i])) ||
			((i == 0 || i == 1) && (tmp[i]->type != cJSON_String ||
					!(valid_hex(tmp[i]->valuestring)))) ||
			((i >= 2 && i <= 5) && (tmp[i]->type != cJSON_Number ||
			(tmp[i]->valuedouble < 0 || tmp[i]->valuedouble > 1))))
			return ("Invalid Jupiter Texture");
	jt->band = create_color(tmp[0]->valuestring);
	jt->background = create_color(tmp[1]->valuestring);
	jt->vortices = tmp[2]->valuedouble;
	jt->bands = tmp[3]->valuedouble;
	jt->perturbations = tmp[4]->valuedouble;
	jt->bands_fade = tmp[5]->valuedouble;
	figure->texture.tx_struct = (void*)jt;
	figure->texture.creating_texture = &jupiter_texture;
	return (0);
}
