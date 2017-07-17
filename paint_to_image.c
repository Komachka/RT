/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:43:23 by kzahreba          #+#    #+#             */
/*   Updated: 2017/04/21 18:43:34 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	paint_image(t_rtv *fr, int x, int y, t_color *cl)
{
	int c;

	c = (y * WX + x) * 4;
	if (c < fr->len && x <= WX && y <= WY && x >= 0 && y >= 0)
	{
		fr->pic[c] = (unsigned char)(cl->b * 255);
		fr->pic[c + 1] = (unsigned char)(cl->g * 255);
		fr->pic[c + 2] = (unsigned char)(cl->r * 255);
		fr->pic[c + 3] = (unsigned char)(cl->al * 100);
	}
}
