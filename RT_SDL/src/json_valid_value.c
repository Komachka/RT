/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_valid_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 01:28:13 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/09/21 01:28:14 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

_Bool	valid_hex(char *str)
{
	if (str && !(ft_strlen(str) % 2) && ft_strlen(str) <= 8)
	{
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9') &&
				!(*str >= 'a' && *str <= 'f') &&
				!(*str >= 'A' && *str <= 'F'))
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

_Bool	valid_color(cJSON *obj, t_color *color)
{
	cJSON	*tmp[4];
	char	*arr[5];

	arr[0] = "Red";
	arr[1] = "Green";
	arr[2] = "Blue";
	arr[3] = "Alpha";
	VAR_INT(index, -1);
	while (++index < 4)
		if (!(tmp[index] = cJSON_GetObjectItemCaseSensitive(obj, arr[index])) ||
			tmp[index]->type != cJSON_Number)
			return (1);
	color->r = tmp[0]->valuedouble;
	color->g = tmp[1]->valuedouble;
	color->b = tmp[2]->valuedouble;
	color->al = tmp[3]->valuedouble;
	return (0);
}
