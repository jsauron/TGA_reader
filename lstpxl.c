/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstpxl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:12:29 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/16 14:23:04 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	fill_maillon(t_tga *tga, t_pixel *curr, int maillon, int mode)
{
	int		pos;

	if (mode == 1)
	{
		pos = maillon * (tga->bits_cm >> 3);
		read_color(curr, tga->bits_cm, tga->colormap, pos);
	}
	else
	{
		pos = maillon * (tga->bitspix >> 3) + tga->len_cm;
		read_color(curr, tga->bitspix, tga->file, pos);
	}
}

void	create_maillon(t_pixel *curr)
{
	curr->next = malloc(sizeof(t_pixel));
	curr->next->bf = curr;
	curr = curr->next;
	curr->next = NULL;
}

void	fill_lst(t_tga *tga, t_pixel *cm, int mode)
{
	int		maillon;
	t_pixel	*curr;
	int		limit;

	maillon = 0;
	limit = (mode == 1) ? tga->len_cm : (tga->w * tga->h);
	printf("limit = %d\n", limit);
	curr = cm;
	while (maillon < limit)
	{
		fill_maillon(tga, curr, maillon, mode);
		maillon++;
		create_maillon(curr);
		if (maillon < limit)
			curr = curr->next;
	}
	curr = cm;
	if (mode == 2)
		printf("PAS DE PALETTE\n");
	while ( curr->next != NULL)
	{
		printf("[%d][%d][%d][%d]\n", curr->a, curr->r, curr->g, curr->b);
		curr = curr->next;
	}
}

void	init_lst(t_pixel *pxl)
{
	pxl->next = NULL;
	pxl->bf = NULL;
}

void	create_lst(t_tga *tga)
{
	if (tga->color_type)
	{
		tga->cm = malloc(sizeof(t_pixel));
		init_lst(tga->cm);
		fill_lst(tga,tga->cm, 1);
	}
	else
	{
		printf("la de dans \n");
		tga->pxl = malloc(sizeof(t_pixel));
		init_lst(tga->pxl);
		fill_lst(tga, tga->pxl, 2);
	}
}
