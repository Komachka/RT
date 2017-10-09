#include "rtv.h"


t_color 	skybox_mapping_texture(t_skybox *skybox, t_vect *point)
{
	t_color col;
	t_vect temp;
	t_mapping_texture *tx;
	double u=0, v=0;
	int x0, x1;

	tx = (t_mapping_texture *)skybox->texture.tx_struct;
	temp = vector_substract(point, &skybox->pos);
	temp = normalize_vector(&temp);
	u = 0.5 + (atan2(temp.z, temp.x) / (2.0 * M_PI));
	v = 0.5 - (asin(temp.y) / M_PI);
	x0 = (u * tx->w);
	x1 = (v * tx->h);
	col = parse_color(tx->arr[x0 + tx->w * x1]);
	return(col);
}

t_color 	creating_skybox(t_rtv *rtv, t_ray *rd)
{
	t_color col;
	t_equation n;
	t_vect dist;
	t_additional s;
	t_ray r;

	r.origin = rtv->skybox.pos;
	r.dir = rd->dir;
	set_zero_color(&col);
	n.a = vector_dot_product(&r.dir, &r.dir);
	dist = vector_substract(&r.origin, &rtv->skybox.pos);
	n.b = 2 * vector_dot_product(&dist, &r.dir);
	n.c = vector_dot_product(&dist, &dist) - (rtv->skybox.r * rtv->skybox.r);
	s.point = intersection_point(select_value(n.root, quadratic_equation(&n)), &r);
	s.mat.cl = rtv->skybox.cl;
	if (rtv->skybox.texturing == ON)
	{
		if (rtv->skybox.texture.type == MAPPING)
			col = skybox_mapping_texture(&rtv->skybox, &s.point);
		else
		{
			rtv->skybox.texture.creating_texture(&s, rtv->skybox.texture.tx_struct);
			col = s.mat.cl;
		}
	}
	else
		col = rtv->skybox.cl;
	return (col);
}
