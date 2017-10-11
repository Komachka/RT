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

#include "rtv.h"

void		threads(t_rtv *rtv)
{
	int			i;
	int 		part;
	pthread_t	trd[NUM_THREADS];
	t_thred		p[NUM_THREADS];

	i = -1;
	part = WY / NUM_THREADS;
	while (++i < NUM_THREADS)
	{
		p[i].rtv1 = rtv;
		p[i].y_start = i * part;
		p[i].y_end = p[i].y_start + part;
		if (i == (NUM_THREADS - 1))
			p[i].y_end = WY;
		p[i].index = i;
		pthread_create(&trd[i], NULL, make_projection, (void *)&p[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(trd[i], NULL);
}