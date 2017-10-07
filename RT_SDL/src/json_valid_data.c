/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_valid_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 01:28:35 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/23 19:37:48 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	valid_id_list(int arr[])
{
	arr[0] = SPHERE;
	arr[1] = PLANE;
	arr[2] = CYLINDER;
	arr[3] = CONE;
	arr[4] = TORUS;
	arr[5] = TRIANGLE;
	arr[6] = DISC;
	arr[7] = ELLIPSOID;
	arr[8] = PARABOLOID;
	arr[9] = LIMITED_CYLINDER;
	arr[10] = LIMITED_CONE;
	arr[11] = LIMITED_PARABOLOID;
	arr[12] = LIMITED_SPHERE;
	arr[13] = PLANE_WITH_HOLE;
}

void	even_more_valid_data(char *arr[], char *type)
{
	if (cmp(type, "Id"))
	{
		arr[0] = "SPHERE";
		arr[1] = "PLANE";
		arr[2] = "CYLINDER";
		arr[3] = "CONE";
		arr[4] = "TORUS";
		arr[5] = "TRIANGLE";
		arr[6] = "DISC";
		arr[7] = "ELLIPSOID";
		arr[8] = "PARABOLOID";
		arr[9] = "LIMITED_CYLINDER";
		arr[10] = "LIMITED_CONE";
		arr[11] = "LIMITED_PARABOLOID";
		arr[12] = "LIMITED_SPHERE";
		arr[13] = "PLANE_WITH_HOLE";
		arr[14] = 0;
	}
	else if (cmp(type, "Objects"))
	{
		arr[0] = "Id";
		arr[1] = "Object";
		arr[2] = "Material";
		arr[3] = 0;
	}
}

void	more_valid_data(char *arr[], char *type)
{
	if (cmp(type, "Light"))
	{
		arr[0] = "Type";
		arr[1] = "Position";
		arr[2] = "Direction";
		arr[3] = "Intensity";
		arr[4] = "Constant Attenuation Coefficient";
		arr[5] = "Linear Attenuation Coefficient";
		arr[6] = "Quadratic Attenuation Coefficient";
		arr[7] = 0;
	}
	else if (cmp(type, "Material"))
	{
		arr[0] = "Color";
		arr[1] = "Ambient";
		arr[2] = "Diffuse";
		arr[3] = "Specular";
		arr[4] = "Shininess";
		arr[5] = "Reflective";
		arr[6] = "Transparency";
		arr[7] = "Refraction";
		arr[8] = 0;
	}
	else
		even_more_valid_data(arr, type);
}

void	valid_data(char *arr[], char *type)
{
	if (cmp(type, "Rtv"))
	{
		arr[0] = "Light Model";
		arr[1] = "Recursive Depth";
		arr[2] = "Samples Grid";
		arr[3] = "Background Color";
		arr[4] = "Ambient Light Intensity";
		arr[5] = "Camera";
		arr[6] = "Light";
		arr[7] = "Objects";
		arr[8] = 0;
	}
	else if (cmp(type, "Camera"))
	{
		arr[0] = "Type";
		arr[1] = "Position";
		arr[2] = "Camera Rotate Angles";
		arr[3] = "FOV";
		arr[4] = 0;
	}
	else
		more_valid_data(arr, type);
}
