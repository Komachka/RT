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
<<<<<<< HEAD
	t_rtv		rtv;
	t_menu		menu;

	rtv.obj = 0;
	ft_menu(&menu, &rtv);
=======
	t_rtv		*rtv;
	t_menu		*menu;
>>>>>>> 995a741a1dc087d3eb58275444604b4689cad7df

	rtv = (t_rtv*)malloc(sizeof(t_rtv));
	menu = (t_menu*)malloc(sizeof(t_menu));
	ft_menu(menu, rtv);
	return (0);
}
