/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_get_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:26:06 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/25 16:08:39 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

char	*get_json_string(const char *name)
{
	int		fd;
	int		bytes;
	char	buff[1024];
	char	*str;

	VAR_INT(file_size, 0);
	str = join("scenes/", name);
	if ((fd = open(str, O_RDONLY)) < 0 || (read(fd, buff, 0)) < 0)
		return (0);
	while ((bytes = read(fd, buff, 1023)))
		file_size += bytes;
	close(fd);
	fd = open(str, O_RDONLY);
	free(str);
	str = (char*)malloc(file_size + 1);
	read(fd, str, file_size);
	str[file_size] = '\0';
	close(fd);
	return (str);
}

void	fill_else(t_rtv *rtv)
{
	rtv->lightening = ON;
	rtv->bg_color = OFF;
	rtv->samples_per_pixel = pow(rtv->samples_grid, 2);
	rtv->samples = rtv->lightening == ON ? rtv->samples_per_pixel : 1;
	rtv->delta_aliasing = 1.0 / (2.0 * rtv->samples_grid);
	//rtv->air_coef = 1.00029; - скоріше за все треба видалити
	rtv->expos = -2.0f;
	rtv->filter.black_and_white = 0;
	rtv->filter.blur = 0;
	rtv->filter.glass = 0;
	rtv->filter.emboss = 0;
	rtv->filter.sepia = 0;
	rtv->filter.negative = 0;
	rtv->filter.romanets = 0;
}

void	get_scene(const char *name, t_rtv *rtv)
{
	char	*str;
	cJSON	*obj;

	str = get_json_string(name);
	if (!(obj = cJSON_Parse(str)))
		put_error("Json Parsing Error At:", cJSON_GetErrorPtr());
	free(str);
	if ((str = validate_rtv(obj, rtv)))
		put_error("[Json RT Error]", str);
	if ((str = validate_camera(cJSON_GetObjectItem(obj, "Camera"), &rtv->cam)))
		put_error("[Json Camera Error]", str);
	if ((str = validate_light(cJSON_GetObjectItem(obj, "Light"), rtv)))
		put_error("[Json Light Error]", str);
	if ((str = validate_objects(cJSON_GetObjectItem(obj, "Objects"), rtv)))
		put_error("[Json Objects Error]", str);
	fill_else(rtv);
}
