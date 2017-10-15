/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 21:28:03 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 20:21:56 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	perlin_noise_texture(t_additional *s, void *t)
{
	int					i;
	double				coef[2];
	t_perlin_texture	*pr;
	t_vect				tmp;
	t_vect				freq;

	pr = (t_perlin_texture *)t;
	freq = pr->frequency;
	coef[1] = pr->amplitude;
	coef[0] = 0;
	i = -1;
	while (++i < pr->octaves)
	{
		tmp = mult_vectors_coordinates(&s->point, &freq);
		coef[0] += calculate_perlin_noise(tmp) * coef[1];
		coef[1] *= pr->persistence;
		freq = mult_vectors_coordinates(&freq, &pr->frequency_att);
	}
	s->mat.cl = calculate_color(pow(coef[0], pr->exponent), &s->mat.cl);
}

void	plasma_texture(t_additional *s, void *t)
{
	t_plasma_texture	*pr;
	double				n[3];
	double				n_sum;

	pr = (t_plasma_texture *)t;
	n[0] = calculate_perlin_noise(s->point);
	n[1] = calculate_perlin_noise(vector_mult(0.5, &s->point));
	n[2] = calculate_perlin_noise(vector_mult(0.25, &s->point));
	n_sum = n[0] + n[1] + n[2];
	s->mat.cl.r = 0.5 * (1.0 + cos(2.0 * M_PI * \
		pr->frequency.r * n_sum + pr->phase.r));
	s->mat.cl.g = 0.5 * (1.0 + cos(2.0 * M_PI * \
		pr->frequency.g * n_sum + pr->phase.g));
	s->mat.cl.b = 0.5 * (1.0 + cos(2.0 * M_PI * \
		pr->frequency.b * n_sum + pr->phase.b));
}

void	contours_texture(t_additional *s, void *t)
{
	t_contours_texture	*pr;
	double				coef;

	pr = (t_contours_texture *)t;
	coef = 0.5 * (1 + sin(2.0 * M_PI * pr->frequency * \
		calculate_perlin_noise(s->point)));
	if (coef > (1.0 - pr->t))
		s->mat.cl = pr->contour;
	else
		s->mat.cl = pr->background;
}

void	caustic_texture(t_additional *s, void *t)
{
	t_caustic_texture	*pr;
	double				n;

	pr = (t_caustic_texture *)t;
	n = calculate_perlin_noise(s->point);
	if (n > 0.5)
		n = 2.0 * (1.0 - n);
	else
		n = 2.0 * n;
	n = 0.3 + 0.9 * n;
	if (n > pr->coverage)
	{
		n = (n - pr->coverage) / (1.2 - pr->coverage);
		n = n * (1.0 + pr->sharpness);
		if (n > 1)
			n = 1;
		s->mat.cl.r = n * pr->color_1.r + (1.0 - n) * pr->color_2.r;
		s->mat.cl.g = n * pr->color_1.g + (1.0 - n) * pr->color_2.g;
		s->mat.cl.b = n * pr->color_1.b + (1.0 - n) * pr->color_2.b;
	}
}

void	jupiter_texture(t_additional *s, void *t)
{
	t_jupiter_texture	*pr;
	double				tt;
	double				w;
	double				ss;
	double				s_;

	pr = (t_jupiter_texture *)t;
	tt = calculate_perlin_noise(create_vector(s->point.x * 20.0, \
		s->point.y * 20.0, s->point.z * 10.00)) / 20.0;
	w = s->point.y + pr->vortices * tt;
	ss = calculate_perlin_noise(create_vector(s->point.x / 1000.0, \
		pr->bands * w, s->point.z / 1000.0));
	s_ = ss + pr->perturbations * ((calculate_perlin_noise(
		create_vector(s->point.x * 50.0, 25.0 * w, s->point.z * 50.0))) - 0.5);
	ss = 0.5 + (s_ - 0.5) * pr->bands_fade;
	s->mat.cl.r = ss * pr->background.r + (1.0 - ss) * pr->band.r;
	s->mat.cl.g = ss * pr->background.g + (1.0 - ss) * pr->band.g;
	s->mat.cl.b = ss * pr->background.b + (1.0 - ss) * pr->band.b;
}
