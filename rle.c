/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:35:19 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/18 16:24:42 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void			rle_uncompress(t_tga *tga)
{
	unsigned char	*new;
	int				index;
	int				index2;
	int				repet;
	int				tmp;

	repet = 0;
	index = 0;
	index2 = 0;
	(new = (unsigned char *)malloc(sizeof(unsigned char) * tga->w * tga->h * 4)) == NULL ? exit(0) : 0;
	if (!tga->len_cm)
	{
		while (repet < (tga->w * tga->h))
		{
			if (tga->file[index] & 0x80) //1er bit == 1 : la couleur qui suit * nb de pixel
			{
				repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]), 1);
				index += ((tga->bitspix >> 3) + 1);
				index2 = (4 * repet);
			}
			else // 1er bit = 0, couleurs qui suivent sont a parser pour chaque nb pixel
			{
				tmp = (tga->file[index] & 0x7F) + 1;
				while (tmp)
				{
					repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]), 0);
					index += 4;
					index2 = (4 * repet);
					tmp--;
				//	printf("Index  : %d\n", index);
			//		printf("Index2 : %d\n", index2);
					//printf("Repet  : %d\n", repet);
				}
				index += 1;
			}
	//		printf("repet2 = %d\n", repet);
		}
		int c;
		c = 0;
		printf("%d\n", tga->w * tga->h);
		while (c/4 < tga->w * tga->h)
		{
			printf("A[%d]\tR[%d]\tG[%d]\tB[%d]\t%d \n", new[c], new[c+1], new[c+2], new[c+3], c / 4);
			c += 4;
		}
		exit(0);
		tga->file = ft_strjoin2(tga->file, new, 0, repet);
	}
}
