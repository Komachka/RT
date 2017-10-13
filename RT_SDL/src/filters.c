/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:00:07 by askochul          #+#    #+#             */
/*   Updated: 2017/09/27 22:21:29 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int	randon(int low, int hight)
{
	double scaled;

	scaled = (double)rand() / RAND_MAX;
	return (int)(low + (hight - low + 1) * scaled + low);
}


void create_filter(t_rtv *rtv)
{
    t_filter filter;

    filter.romanets = 0;
    filter.negative = 0;
    filter.sepia = 0;
    filter.emboss = 0;
    filter.glass = 0;
    filter.blur = 0;
    filter.black_and_white = 0;
    rtv->filter = filter;
}


void	copy_to_filter(t_rtv *rtv)
{
	int i;
    int j;
	
    i = 0;
	while (i <= WY)
	{
		j = 0;
		while (j <= WX)
		{
	    
          rtv->filter.sdl_col_with_filter[i][j] = rtv->s_c[i][j];
		  j++;
		}
		i++;
	}
}

void	create_sepia_filter(t_rtv *rtv, int red, int green, int blue)
{
	int i;
	int j;

	i = 0;
	while (i <= WY)
	{
		j = 0;
		while (j <= WX)
		{
			red = (0.393 * rtv->filter.sdl_col_with_filter[i][j].r + 0.769
* rtv->filter.sdl_col_with_filter[i][j].g + 0.189 * rtv->filter.sdl_col_with_filter[i][j].b);
			green = (0.349 * rtv->filter.sdl_col_with_filter[i][j].r + 0.686
* rtv->filter.sdl_col_with_filter[i][j].g + 0.168 * rtv->filter.sdl_col_with_filter[i][j].b);
			blue = (0.272 * rtv->filter.sdl_col_with_filter[i][j].r + 0.534
* rtv->filter.sdl_col_with_filter[i][j].g + 0.131 * rtv->filter.sdl_col_with_filter[i][j].b);
			rtv->filter.sdl_col_with_filter[i][j].r = MIN(red, 255);
			rtv->filter.sdl_col_with_filter[i][j].g = MIN(green, 255);
			rtv->filter.sdl_col_with_filter[i][j].b = MIN(blue, 255);
			j++;
		}
		i++;
	}
}

void	create_b_n_w_filter(t_rtv *rtv)
{
	int i;
	int j;
	int midle;

	i = 0;
	midle = 0;
	while (i < WY)
	{
		j = 0;
		while (j < WX)
		{
			midle = (rtv->s_c[i][j].r + rtv->s_c[i][j].g + rtv->s_c[i][j].b) / 3;
			rtv->filter.sdl_col_with_filter[i][j].r = midle;
			rtv->filter.sdl_col_with_filter[i][j].g = midle;
			rtv->filter.sdl_col_with_filter[i][j].b = midle;
			j++;
		}
		i++;
	}
}

void	create_negative_filter(t_rtv *rtv)
{
	int i;
	int j;

	i = 0;
	while (i < WY)
	{
		j = 0;
		while (j < WX)
		{
			rtv->filter.sdl_col_with_filter[i][j].r = 255 - rtv->filter.sdl_col_with_filter[i][j].r;
			rtv->filter.sdl_col_with_filter[i][j].g = 255 - rtv->filter.sdl_col_with_filter[i][j].g;
			rtv->filter.sdl_col_with_filter[i][j].b = 255 - rtv->filter.sdl_col_with_filter[i][j].b;
			j++;
		}
		i++;
	}
}





void foo_b(double *red, double *green, double *blue, t_tmp tmp)
{
    t_rtv *rtv;
    int imageX;
    int imageY;
    static double filter[fH][fW] ={{0, 0, 1, 0, 0},{0, 1, 1, 1, 0},{1, 1, 1, 1, 1},{0, 1, 1, 1, 0},{0, 0, 1, 0, 0}};



    rtv = tmp.rtv;

    tmp.filterY = 0;
    while (tmp.filterY < fH)
    {
        tmp.filterX = 0;
        while (tmp.filterX < fW)
        {
            imageX = (tmp.x - fW / 2 + tmp.filterX + WX) % WX;
            imageY = (tmp.y - fH / 2 + tmp.filterY + WY) % WY;
            *red += rtv->filter.sdl_col_with_filter[imageY][imageX].r * filter[tmp.filterY][tmp.filterX];
            *green += rtv->filter.sdl_col_with_filter[imageY][imageX].g * filter[tmp.filterY][tmp.filterX];
            *blue += rtv->filter.sdl_col_with_filter[imageY][imageX].b * filter[tmp.filterY][tmp.filterX];
            tmp.filterX++;
        }
        tmp.filterY++;
    }

}

void	create_blur_filter(t_rtv *rtv, double red, double green, double blue)
{

   t_tmp tmp;
     tmp.x = 0;
     tmp.filterY = 0;
     tmp.filterX = 0;
     tmp.rtv = rtv;     

     
    
    

     while (tmp.x < WX)
     {
        tmp.y = 0;
        while (tmp.y < WY)
        {   red = 0.0, blue = 0.0, green = 0.0;
            foo_b(&red, &green, &blue, tmp);
            



            rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].r = MIN(MAX((double)(1.0 / 13.0) * red, 0), 255);
            rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].g = MIN(MAX((double)(1.0 / 13.0) * green, 0), 255);
            rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].b = MIN(MAX((double)(1.0 / 13.0) * blue, 0), 255);
            tmp.y++;
        }





        tmp.x++;
     }



}


void foo_e(double *red, double *green, double *blue, t_tmp tmp)
{
    t_rtv *rtv;
    int imageX;
    int imageY;
     static double filter[fH][fW] ={{-1,  0, 0, 0, 0},{0, -2,  0,  0,  0},{0,  0,  6,  0,  0},{0,  0,  0, -2,  0},
{0,  0,  0,  0, -1}};


    rtv = tmp.rtv;

    tmp.filterY = 0;
    while (tmp.filterY < fH)
    {
        tmp.filterX = 0;
        while (tmp.filterX < fW)
        {
            imageX = (tmp.x - fW / 2 + tmp.filterX + WX) % WX;
            imageY = (tmp.y - fH / 2 + tmp.filterY + WY) % WY;
            *red += rtv->filter.sdl_col_with_filter[imageY][imageX].r * filter[tmp.filterY][tmp.filterX];
            *green += rtv->filter.sdl_col_with_filter[imageY][imageX].g * filter[tmp.filterY][tmp.filterX];
            *blue += rtv->filter.sdl_col_with_filter[imageY][imageX].b * filter[tmp.filterY][tmp.filterX];
            tmp.filterX++;
        }
        tmp.filterY++;
    }

}



void create_emboss_filter(t_rtv *rtv, double red, double green, double blue)
{

   t_tmp tmp;
     tmp.x = 0;
     tmp.filterY = 0;
     tmp.filterX = 0;
     tmp.rtv = rtv;  

while (tmp.x < WX)
     {
        tmp.y = 0;
        while (tmp.y < WY)
        {   red = 0.0, blue = 0.0, green = 0.0;
            foo_e(&red, &green, &blue, tmp);
            



            rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].r = MIN(MAX(red, 0), 255);
            rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].g = MIN(MAX(green, 0), 255);
            rtv->filter.sdl_col_with_filter[tmp.y][tmp.x].b = MIN(MAX(blue, 0), 255);
            tmp.y++;
        }





        tmp.x++;
     }

}

unsigned int	rand_interval(unsigned int min, unsigned int max)
{
	int r;
	unsigned int range = 1 + max - min;
	unsigned int buckets = RAND_MAX / range;
	unsigned int limit = buckets * range;

	r = rand();
	while (r >= (int)limit)
		r = rand();
	return min + (r / buckets);
}



void create_glass_filter(t_rtv *rtv)
{
	int x;
	int y;
	int imageX;
	int imageY;

	x = 0;

    while  (x < WX)
    {
        y = 0;
        while (y < WY)
        {
            imageX = rand_interval(x, x + 5);
            imageY = rand_interval(y, y + 5);
            if (imageX < WX && imageY < WY)
            {
                rtv->filter.sdl_col_with_filter[y][x].r = rtv->filter.sdl_col_with_filter[imageY][imageX].r;
                rtv->filter.sdl_col_with_filter[y][x].g = rtv->filter.sdl_col_with_filter[imageY][imageX].g;
                rtv->filter.sdl_col_with_filter[y][x].b = rtv->filter.sdl_col_with_filter[imageY][imageX].b;
            }
            y++;
        }
        x++;
    }

}

void create_sromanets(t_rtv *rtv)
{
	int k;
	int x;
	int y;
	int imageX;
	int imageY;

	k = 0;

    while  (k < 5)
    {
        x = 0;
        while (x < WX) {
            y = 0;
            while (y < WY) {
                imageX = randon(x, x + 5);
                imageY = randon(y, y + 5);
                if (imageX < WX && imageY < WY) {
                    rtv->filter.sdl_col_with_filter[y][x].r = rtv->filter.sdl_col_with_filter[imageY][imageX].r;
                    rtv->filter.sdl_col_with_filter[y][x].g = rtv->filter.sdl_col_with_filter[imageY][imageX].g;
                    rtv->filter.sdl_col_with_filter[y][x].b = rtv->filter.sdl_col_with_filter[imageY][imageX].b;
                }
                y++;
            }
            x++;
        }
    k++;
    }

}

void correct_exposure(t_rtv *rtv, t_color *color)
{
	float exposure;

	exposure = rtv->expos;
	color->r = 1.0f - exp(color->r * exposure);
	color->g = 1.0f - exp(color->g* exposure);
	color->b = 1.0f - exp(color->b * exposure);
}
