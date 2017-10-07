/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:11:38 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/02 16:32:21 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	fill_struct(t_rtv *rtv)
{
	rtv->sk = OFF;
	rtv->skybox.pos = rtv->cam.pos;
	rtv->skybox.r = 1000;
}

int		main(void)
{
	t_rtv		rtv;
	t_menu		menu;

	ft_menu(&menu, &rtv);
	get_scene("scenes/scene1.json", &rtv);
	fill_struct(&rtv); // додати в зчитування
	basic_function(&rtv);
	return (0);
}
