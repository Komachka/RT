/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:00:07 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:09:53 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void			correct_exposure(t_rtv *rtv, t_color *color)
{
	float exposure;

	exposure = rtv->expos;
	color->r = 1.0f - exp(color->r * exposure);
	color->g = 1.0f - exp(color->g * exposure);
	color->b = 1.0f - exp(color->b * exposure);
}
