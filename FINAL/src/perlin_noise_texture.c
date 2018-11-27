/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:54:06 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 20:57:12 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

#define I 0
#define XI 1
#define YI 2
#define ZI 3
#define AAA 4
#define ABA 5
#define AAB 6
#define ABB 7
#define BAA 8
#define BBA 9
#define BAB 10
#define BBB 11
#define XF 3
#define YF 4
#define ZF 5
#define X1 6
#define X2 7
#define Y1 8
#define Y2 9
#define U 10
#define V 11
#define W 12
#define LERP(a, b, x) ((a) + ((x) * ((b) - (a))))
#define FADE(t) ((t) * (t) * (t) * ((t) * ((t) * 6.0 - 15.0) + 10.0))

static inline double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = h < 8 ? x : y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

static inline double	more_calculate(int *integer, const int *p, double *dbl)
{
	integer[AAA] = p[p[p[integer[XI]] + integer[YI]] + integer[ZI]];
	integer[ABA] = p[p[p[integer[XI]] + integer[YI] + 1] + integer[ZI]];
	integer[AAB] = p[p[p[integer[XI]] + integer[YI]] + integer[ZI] + 1];
	integer[ABB] = p[p[p[integer[XI]] + integer[YI] + 1] + integer[ZI] + 1];
	integer[BAA] = p[p[p[integer[XI] + 1] + integer[YI]] + integer[ZI]];
	integer[BBA] = p[p[p[integer[XI] + 1] + integer[YI] + 1] + integer[ZI]];
	integer[BAB] = p[p[p[integer[XI] + 1] + integer[YI]] + integer[ZI] + 1];
	integer[BBB] = p[p[p[integer[XI] + 1] + integer[YI] + 1] + integer[ZI] + 1];
	dbl[X1] = LERP(grad(integer[AAA], dbl[XF], dbl[YF], dbl[ZF]),
					grad(integer[BAA], dbl[XF] - 1, dbl[YF], dbl[ZF]), dbl[U]);
	dbl[X2] = LERP(grad(integer[ABA], dbl[XF], dbl[YF] - 1, dbl[ZF]),
				grad(integer[BBA], dbl[XF] - 1, dbl[YF] - 1, dbl[ZF]), dbl[U]);
	dbl[Y1] = LERP(dbl[X1], dbl[X2], dbl[V]);
	dbl[X1] = LERP(grad(integer[AAB], dbl[XF], dbl[YF], dbl[ZF] - 1),
				grad(integer[BAB], dbl[XF] - 1, dbl[YF], dbl[ZF] - 1), dbl[U]);
	dbl[X2] = LERP(grad(integer[ABB], dbl[XF], dbl[YF] - 1, dbl[ZF] - 1),
					grad(integer[BBB], dbl[XF] - 1, dbl[YF] - 1, dbl[ZF] - 1),
					dbl[U]);
	dbl[Y2] = LERP(dbl[X1], dbl[X2], dbl[V]);
	return (LERP(dbl[Y1], dbl[Y2], dbl[W]) + 1.0) / 2.0;
}

static inline double	continue_calculate(double *dbl, const int *permutation)
{
	int			integer[12];
	int			p[512];

	integer[I] = -1;
	while (++integer[I] < 512)
		p[integer[I]] = permutation[integer[I] % 256];
	integer[XI] = (int)floor(dbl[X]) & 255;
	integer[YI] = (int)floor(dbl[Y]) & 255;
	integer[ZI] = (int)floor(dbl[Z]) & 255;
	dbl[XF] = dbl[X] - (int)floor(dbl[X]);
	dbl[YF] = dbl[Y] - (int)floor(dbl[Y]);
	dbl[ZF] = dbl[Z] - (int)floor(dbl[Z]);
	dbl[U] = FADE(dbl[XF]);
	dbl[V] = FADE(dbl[YF]);
	dbl[W] = FADE(dbl[ZF]);
	return (more_calculate(integer, p, dbl));
}

double					calculate_perlin_noise(t_vect point)
{
	double		dbl[13];
	static int	permutation[] = {151, 160, 137, 91, 90, 15, 131, 13, 201, 95,
		96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240,
		21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
		219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174,
		20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
		77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105,
		92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216,
		80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116,
		188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
		124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
		227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248,
		152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129,
		22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104,
		218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179,
		162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181,
		199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
		138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78,
		66, 215, 61, 156, 180};

	dbl[X] = point.x;
	dbl[Y] = point.y;
	dbl[Z] = point.z;
	return (continue_calculate(dbl, permutation));
}
