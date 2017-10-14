/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:11:38 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 17:49:55 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		main(void)
{
	t_menu		*menu;
	t_rtv		*rtv;

	menu = (t_menu*)malloc(sizeof(t_menu));
	rtv = (t_rtv*)malloc(sizeof(t_rtv));
	rtv->obj = 0;
	ft_menu(menu, rtv);
	free(rtv);
	exit(0);
	return (0);
}
