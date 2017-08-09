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
	pthread_t	trd[NUM_THREADS];
	t_thred		p[NUM_THREADS];

	i = -1;
	while (++i < NUM_THREADS)
	{
		p[i].rtv1 = rtv;
		p[i].y = i * WY / NUM_THREADS;
		pthread_create(&trd[i], NULL, make_projection, (void *)&p[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(trd[i], NULL);
}
