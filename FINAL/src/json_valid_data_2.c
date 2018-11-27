/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_valid_data_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 01:28:35 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 19:37:48 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	valid_id_list_2(int arr[])
{
	arr[0] = PERLIN;
	arr[1] = MAPPING;
	arr[2] = PLASMA;
	arr[3] = CONTOURS;
	arr[4] = CAUSTIC;
	arr[5] = JUPITER;
}

void	valid_data_2(char *arr[], char *type)
{
	if (cmp(type, "Textures"))
	{
		arr[0] = "PERLIN";
		arr[1] = "MAPPING";
		arr[2] = "PLASMA";
		arr[3] = "CONTOURS";
		arr[4] = "CAUSTIC";
		arr[5] = "JUPITER";
	}
	else if (cmp(type, "Jupiter"))
	{
		arr[0] = "Band";
		arr[1] = "Background";
		arr[2] = "Vortices";
		arr[3] = "Bands";
		arr[4] = "Perturbations";
		arr[5] = "Bands Fade";
	}
}
