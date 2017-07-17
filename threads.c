/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:47:31 by kzahreba          #+#    #+#             */
/*   Updated: 2017/03/15 16:39:42 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		threads(t_rtv *rtv)
{
	int			i;
	pthread_t	trd[4];
	t_thred		p[4];

	i = -1;
	while (++i < 4)
	{
		p[i].rtv1 = rtv;
		p[i].y = i * WY / 4;
		pthread_create(&trd[i], NULL, make_projection, (void *)&p[i]);
	}
	i = -1;
	while (++i < 4)
		pthread_join(trd[i], NULL);
}
