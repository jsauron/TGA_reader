/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pxl_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:47:12 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/15 17:24:33 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void		fill_value(t_pixel *pxl, t_pixel *pos)
{
	pxl->a = pos->a;
	pxl->r = pos->r;
	pxl->g = pos->g;
	pxl->b = pos->b;
}

void		fill_pxl(t_tga *tga, t_pixel *pxl)
{
	int		last;
	int		diff;
	int		i;
	t_pixel	*pos;
	t_pixel	*curr;

	diff = 0;
	last = 0;
	i = 0;
	pos = tga->cm;
	curr = pxl;
	while (i < (tga->w * tga->h))
	{
		diff = tga->file[i] - last;
		while (diff)
		{
			if (diff > 0)
			{
				pos = pos->next;
				diff--;
			}
			else
			{
				pos = pos->bf;
				diff++;
			}
		}
		fill_value(curr, pos);
		last = tga->file[i];
		create_maillon(curr);
		curr = curr->next;
		i++;
	}
	curr = pxl;
	int	check;
	check=0;
	while(curr->next != NULL)
	{
		printf("[%d][%d][%d][%d] \t%d\n", curr->a, curr->r, curr->g, curr->b, check);
		check++;
		curr = curr->next;
	}
}

void		range_pxl(t_tga *tga)
{
	if (tga->len_cm != 0)
	{
		tga->pxl = malloc(sizeof(t_pixel));
		init_lst(tga->pxl);
		fill_pxl(tga, tga->pxl);
	}
}
