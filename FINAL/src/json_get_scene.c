/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_get_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:26:06 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 13:19:23 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline char	*get_json_string(const char *name)
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

static inline void	fill_else(t_rtv *rtv)
{
	rtv->lightening = ON;
	rtv->bg_color = OFF;
	rtv->samples_per_pixel = pow(rtv->samples_grid, 2);
	rtv->samples = rtv->lightening == ON ? rtv->samples_per_pixel : 1;
	rtv->grid = rtv->lightening == ON ? rtv->samples_grid : 1;
	rtv->delta_aliasing = 1.0 / (2.0 * rtv->samples);
	rtv->expos = -2.0f;
	rtv->filter.black_and_white = 0;
	rtv->filter.blur = 0;
	rtv->filter.glass = 0;
	rtv->filter.emboss = 0;
	rtv->filter.sepia = 0;
	rtv->filter.negative = 0;
	rtv->filter.romanets = 0;
	rtv->def_cam_pos = rtv->cam.pos;
	rtv->def_cam_dir[0] = rtv->cam.rotate[0];
	rtv->def_cam_dir[1] = rtv->cam.rotate[1];
	rtv->def_cam_dir[2] = rtv->cam.rotate[2];
	rtv->delphin = ON;
}

void				get_scene(const char *name, t_rtv *rtv)
{
	char	*str;
	cJSON	*tmp[4];

	str = get_json_string(name);
	if (!(rtv->obj = cJSON_Parse(str)))
		put_error("Json Parsing Error ", 0);
	free(str);
	if ((str = validate_rtv(rtv->obj, rtv)))
		put_error("[Json RT Error]", str);
	tmp[0] = cJSON_GetObjectItemCaseSensitive(rtv->obj, "Camera");
	tmp[1] = cJSON_GetObjectItemCaseSensitive(rtv->obj, "Skybox");
	tmp[2] = cJSON_GetObjectItemCaseSensitive(rtv->obj, "Light");
	tmp[3] = cJSON_GetObjectItemCaseSensitive(rtv->obj, "Objects");
	if ((str = validate_camera(tmp[0], &rtv->cam)))
		put_error("[Json Camera Error]", str);
	if ((str = validate_skybox(tmp[1], rtv)))
		put_error("[Json Skybox Error]", str);
	if ((str = validate_light(tmp[2], rtv)))
		put_error("[Json Light Error]", str);
	if ((str = validate_objects(tmp[3], rtv)))
		put_error("[Json Objects Error]", str);
	fill_else(rtv);
}
