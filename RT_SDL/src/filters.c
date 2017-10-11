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
    int i;


    t_filter filter;

    filter.romanets = 0;
    filter.negative = 0;
    filter.sepia = 0;
    filter.emboss = 0;
    filter.glass = 0;
    filter.blur = 0;
    filter.black_and_white = 0;


    SDL_Color **colours2;
    colours2 = (SDL_Color**)malloc(sizeof(SDL_Color*) * WX);
    i = 0;
    while (i < WX)
    {
        colours2[i] = (SDL_Color*)malloc(sizeof(SDL_Color) * WY);
        i++;
    }
    filter.sdl_col_with_filter = colours2;
    rtv->filter = filter;


}


void	copy_to_filter(t_rtv *rtv)
{
	int i;
    int j;
	
    i = 0;
	while (i < WY)
	{
		j = 0;
		while (j < WX)
		{
	       rtv->filter.sdl_col_with_filter[j][i] = rtv->s_c[j][i];
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
	while (i < WY)
	{
		j = 0;
		while (j < WX)
		{
			red = (0.393 * rtv->filter.sdl_col_with_filter[j][i].r + 0.769 * rtv->filter.sdl_col_with_filter[j][i].g + 0.189 * rtv->filter.sdl_col_with_filter[j][i].b);
			green = (0.349 * rtv->filter.sdl_col_with_filter[j][i].r + 0.686 * rtv->filter.sdl_col_with_filter[j][i].g + 0.168 * rtv->filter.sdl_col_with_filter[j][i].b);
			blue = (0.272 * rtv->filter.sdl_col_with_filter[j][i].r + 0.534 * rtv->filter.sdl_col_with_filter[j][i].g + 0.131 * rtv->filter.sdl_col_with_filter[j][i].b);
			rtv->filter.sdl_col_with_filter[j][i].r = MIN(red, 255);
			rtv->filter.sdl_col_with_filter[j][i].g = MIN(green, 255);
			rtv->filter.sdl_col_with_filter[j][i].b = MIN(blue, 255);
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
			midle = (rtv->s_c[j][i].r + rtv->s_c[j][i].g + rtv->s_c[j][i].b) / 3;
			rtv->filter.sdl_col_with_filter[j][i].r = midle;
			rtv->filter.sdl_col_with_filter[j][i].g = midle;
			rtv->filter.sdl_col_with_filter[j][i].b = midle;
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
			rtv->filter.sdl_col_with_filter[j][i].r = 255 - rtv->filter.sdl_col_with_filter[j][i].r;
			rtv->filter.sdl_col_with_filter[j][i].g = 255 - rtv->filter.sdl_col_with_filter[j][i].g;
			rtv->filter.sdl_col_with_filter[j][i].b = 255 - rtv->filter.sdl_col_with_filter[j][i].b;
			j++;
		}
		i++;
	}
}

void	create_blur_filter(t_rtv *rtv, double red, double green, double blue)
{

    int const fW = 5;
    int const fH = 5;
    double filter[fH][fW] =
            {
                   { 0, 0, 1, 0, 0},
                   { 0, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1},
                    {0, 1, 1, 1, 0},
                    {0, 0, 1, 0, 0}
            };

    double factor = 1.0 / 13.0;
    double bias = 0.0;
    int x = 0;
    int y = 0;
    int filterX = 0;
    int filterY = 0;
    int imageX;
    int imageY;

    while (x < WX)
    {
        y = 0;
        while (y < WY)
        {

            red = 0.0, blue = 0.0, green = 0.0;
            filterY = 0;
            while (filterY < fH)
            {
                filterX = 0;
                while (filterX < fW)

                {

                    imageX = (x - fW / 2 + filterX + WX) % WX;
                    imageY = (y - fH / 2 + filterY + WY) % WY;
                    red += rtv->filter.sdl_col_with_filter[imageX][imageY].r * filter[filterY][filterX];
                    green += rtv->filter.sdl_col_with_filter[imageX][imageY].g * filter[filterY][filterX];
                    blue += rtv->filter.sdl_col_with_filter[imageX][imageY].b * filter[filterY][filterX];
                    filterX++;
                }
                filterY++;
            }

            rtv->filter.sdl_col_with_filter[x][y].r = MIN(MAX(factor * red + bias, 0), 255);
            rtv->filter.sdl_col_with_filter[x][y].g = MIN(MAX(factor * green + bias, 0), 255);
            rtv->filter.sdl_col_with_filter[x][y].b = MIN(MAX(factor * blue + bias, 0), 255);


            y++;
        }
        x++;
    }
}

#define fW 5
#define fH 5

void create_emboss_filter(t_rtv *rtv, double red, double green, double blue)
{
    double filter[fH][fW] =
            {
                {-1,  0,  0,  0,  0},
                {0, -2,  0,  0,  0},
                {0,  0,  6,  0,  0},
                {0,  0,  0, -2,  0},
                {0,  0,  0,  0, -1}
            };

    double factor = 1.0;
    double bias = 0.0;


    int x = 0;
    int y = 0;
    int filterX = 0;
    int filterY = 0;
    int imageX;
    int imageY;

    while (x < WX)
    {
        y = 0;
        while (y < WY)
        {
            red = 0.0, blue = 0.0, green = 0.0;
            filterY = 0;
            while (filterY < fH)
            {
                filterX = 0;
                while (filterX < fW)
                {
                    imageX = (x - fW / 2 + filterX + WX) % WX;
                    imageY = (y - fH / 2 + filterY + WY) % WY;
                    red += rtv->filter.sdl_col_with_filter[imageX][imageY].r * filter[filterY][filterX];
                    green += rtv->filter.sdl_col_with_filter[imageX][imageY].g * filter[filterY][filterX];
                    blue += rtv->filter.sdl_col_with_filter[imageX][imageY].b * filter[filterY][filterX];
                    filterX++;
                }
                filterY++;
            }
            rtv->filter.sdl_col_with_filter[x][y].r = MIN(MAX(factor * red + bias, 0), 255);
            rtv->filter.sdl_col_with_filter[x][y].g = MIN(MAX(factor * green + bias, 0), 255);
            rtv->filter.sdl_col_with_filter[x][y].b = MIN(MAX(factor * blue + bias, 0), 255);
            y++;
        }
        x++;
    }
}

unsigned int	rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

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
                rtv->filter.sdl_col_with_filter[x][y].r = rtv->filter.sdl_col_with_filter[imageX][imageY].r;
                rtv->filter.sdl_col_with_filter[x][y].g = rtv->filter.sdl_col_with_filter[imageX][imageY].g;
                rtv->filter.sdl_col_with_filter[x][y].b = rtv->filter.sdl_col_with_filter[imageX][imageY].b;
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
                    rtv->filter.sdl_col_with_filter[x][y].r = rtv->filter.sdl_col_with_filter[imageX][imageY].r;
                    rtv->filter.sdl_col_with_filter[x][y].g = rtv->filter.sdl_col_with_filter[imageX][imageY].g;
                    rtv->filter.sdl_col_with_filter[x][y].b = rtv->filter.sdl_col_with_filter[imageX][imageY].b;
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
