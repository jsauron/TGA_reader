/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstpxl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:12:29 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/19 12:15:12 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	fill_pxl(t_tga *tga, int i, int mode)
{
	int		pos;

	if (mode == 1)
	{
		pos = i * (tga->bits_cm >> 3);
		read_color(&tga->cm[i], tga->bits_cm, tga->colormap, pos);
	}
	else
	{
		pos = i * (tga->bitspix >> 3) + tga->len_cm;
		read_color(&tga->pxl[i], tga->bitspix, tga->file, pos);
	}
}

void	fill_data(t_tga *tga, int mode)
{
	int		i;
//	t_pixel	*pxl;
	int		limit;

	i = 0;
	limit = (mode == 1) ? tga->len_cm : (tga->w * tga->h);
	printf("limit = %d\n", limit);
	while (i < limit)
	{
		fill_pxl(tga, i, mode);
		i++;
	}
	if (mode == 2)
		printf("PAS DE PALETTE\n");
	i = 0;
	while (i < limit)
	{
		printf("A[%d]R[%d]G[%d]B[%d]\n", tga->pxl[i].a, tga->pxl[i].r, tga->pxl[i].g, tga->pxl[i].b);
		i++;
	}
}

void	create_pxl(t_tga *tga)
{
	if (tga->color_type)
	{
		tga->cm = malloc(sizeof(t_pixel) * tga->len_cm);
		fill_data(tga, 1);
	}
	else
	{
		tga->pxl = malloc(sizeof(t_pixel) * (tga->w * tga->h));
		fill_data(tga, 2);
	}
}
