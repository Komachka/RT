/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:54:06 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/01 20:50:56 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double  fade(double t) 
{
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

double lerp(double a, double b, double x) 
{
	return a + x * (b - a);
}

double grad(int hash, double x, double y, double z)
{
	int h = hash & 15;									
	double u = h < 8 ? x : y;
	double v;											
	if(h < 4)
		v = y;
	else if(h == 12 || h == 14 )
		v = x;
	else
		v = z;
	return ((h&1) == 0 ? u : -u)+((h&2) == 0 ? v : -v);
}

void 	perlin_noise_texture(t_additional *s, void *t) 
{
	double coef = 0;
	t_rtv *rtv;
	rtv = (t_rtv *)t;
	t_texture *txt;
	txt = &rtv->objects[s->figure].texture;
	t_perlin_texture *pr;
	pr = (t_perlin_texture *)txt->tx_struct;

	t_vect tmp;
	t_vect freq = pr->frequency;
	int i;
	double ampl = pr->amplitude;
	i = -1;
	while (++i < pr->octaves)
	{
		tmp.x = s->point.x * freq.x;
		tmp.y = s->point.y * freq.y;
		tmp.z = s->point.z * freq.z;
		coef += calculate_perlin_noise(tmp) * ampl;
		ampl *= pr->persistence;
		freq.x *= pr->frequency_att.x;
		freq.y *= pr->frequency_att.y;
		freq.z *= pr->frequency_att.z;
	}

	coef = pow(coef, pr->exponent);
	s->mat.cl = calculate_color(coef, &s->mat.cl);
}

double	calculate_perlin_noise(t_vect point)
{
	int i;
	int xi;
	int yi;
	int zi;
	double xf;
	double yf;
	double zf;
	double u;
	double v;
	double w;
	double x1;
	double x2;
	double y1;
	double y2;
	int aaa, aba, aab, abb, baa, bba, bab, bbb;
	i = -1;
	double x = point.x;
	double y = point.y;
	double z = point.z;
	int permutation[] = { 151,160,137,91,90,15,					
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};
	int p[512];
	while (++i < 512)
		p[i] = permutation[i%256];


	xi =  (int)floor(x) & 255;
	yi =  (int)floor(y) & 255;
	zi =  (int)floor(z) & 255;

	xf = x - (int)floor(x);
	yf = y - (int)floor(y);
	zf = z - (int)floor(z);

	u = fade(xf);
	v = fade(yf);
	w = fade(zf);

	aaa = p[p[p[xi] + yi] + zi];
	aba = p[p[p[xi] + yi + 1] + zi];
	aab = p[p[p[xi] + yi] + zi + 1];
	abb = p[p[p[xi]+ yi + 1] + zi + 1];
	baa = p[p[p[xi + 1] + yi] + zi];
	bba = p[p[p[xi + 1] + yi + 1] + zi];
	bab = p[p[p[xi + 1] + yi] + zi + 1];
	bbb = p[p[p[xi + 1]+ yi + 1] + zi + 1];
	x1 = lerp(grad(aaa, xf, yf, zf),	grad(baa, xf - 1, yf, zf),	u);
	x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
	y1 = lerp(x1, x2, v);
	x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);
	x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);
	y2 = lerp (x1, x2, v);
	return (lerp (y1, y2, w) + 1.0) / 2.0;
}
