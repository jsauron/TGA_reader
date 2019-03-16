/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstpxl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:12:29 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/16 11:00:23 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	fill_maillon(t_tga *tga, t_pixel *curr, int maillon, int mode)
{
	int		pos;

	if (mode == 1)
	{
		pos = maillon * (tga->bits_cm >> 3);
		if (tga->bits_cm == 32)
		{
			curr->a = tga->colormap[pos + 3];
			curr->r = tga->colormap[pos + 2];
			curr->g = tga->colormap[pos + 1];
			curr->b = tga->colormap[pos];
		}
		else if (tga->bits_cm == 24)
		{
			curr->r = tga->colormap[pos + 2];
			curr->g = tga->colormap[pos + 1];
			curr->b = tga->colormap[pos];
		}
		else if (tga->bits_cm == 16 || tga->bits_cm == 15)
		{
			if (tga->bits_cm == 16)
				curr->a = tga->colormap[pos + 1] & 0x80 ? 255 : 0;
			curr->r = (tga->colormap[pos + 1] & 0x7C) * 255 / 31;
			curr->g = (tga->colormap[pos + 1] & 0x3) << 6;
			curr->g += (tga->colormap[pos] & 0xE0) >> 2;
			curr->b = (tga->colormap[pos] & 0x1F) * 255 / 31;
		}
		else if (tga->bits_cm == 8)
		{
			curr->r = tga->colormap[pos];
			curr->g = tga->colormap[pos];
			curr->b = tga->colormap[pos];
		}
	}
	else
	{
		pos = maillon * (tga->bitspix >> 3) + tga->len_cm;
		if (tga->bitspix == 32)
		{
			curr->a = tga->file[pos + 3];
			curr->r = tga->file[pos + 2];
			curr->g = tga->file[pos + 1];
			curr->b = tga->file[pos];
		}
		else if (tga->bitspix == 24)
		{
			curr->r = tga->file[pos + 2];
			curr->g = tga->file[pos + 1];
			curr->b = tga->file[pos];
		}
		else if (tga->bitspix == 16 || tga->bitspix == 15)
		{
			if (tga->bitspix == 16)
				curr->a = tga->file[pos + 1] & 0x80 ? 255 : 0;
			curr->r = (tga->file[pos + 1] & 0x7C) * 255 / 31;
			curr->g = (tga->file[pos + 1] & 0x3) << 6;
			curr->g += (tga->file[pos] & 0xE0) >> 2;
			curr->b = (tga->file[pos] & 0x1F) * 255 / 31;
		}
		else if (tga->bitspix == 8)
		{
			curr->r = tga->file[pos];
			curr->g = tga->file[pos];
			curr->b = tga->file[pos];
		}
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
		tga->pxl = malloc(sizeof(t_pixel));
		init_lst(tga->pxl);
		fill_lst(tga, tga->pxl, 2);
	}
}
