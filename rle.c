/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:35:19 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/16 17:03:50 by jsauron          ###   ########.fr       */
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
			printf("FILE +> [%d]\n", tga->file[index]);
			if (tga->file[index] & 0x80)
			{
				repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]), 1);
				index += (tga->bitspix >> 3) + 1;
				index2 = ((tga->bitspix >> 3) * repet);
			}
			else
			{
				tmp = (tga->file[index] & 0x7F) + 1;
				printf("repet not compress %d\n", tmp);
				while (tmp)
				{
					repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]), 0);
					index += (tga->bitspix >> 3);
					index2 = ((tga->bitspix >> 3) * repet);
					tmp--;
					printf("Index  : %d\n", index);
					printf("Index2 : %d\n", index2);
					printf("Repet  : %d\n", repet);
				}
				index += 1;
			}
			printf("IND2 = %d \tIND = %d\n", index2 ,index);







		/*	repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]));
			index += tga->file[index] & 0x80 ? (tga->bitspix >> 3) + 1 : (((tga->file[index] & 0x7F) + 1) * tga->bitspix >> 3);
			index2 = ((tga->bitspix >> 3) * repet);
			printf("repet = %d\n", repet);
			printf("AFTER => IND2 = %d \tIND = %d\n", index2 ,index);
		*/}
	}
	int c;
	c = 0;
	while (c < repet * (tga->bitspix >> 3))
	{
		printf("[%d]\t[%d]\t[%d]\t[%d]\t%d \n", new[c], new[c+1], new[c+2], new[c+3], c / (tga->bitspix >> 3));
		c+=(tga->bitspix >> 3);
	}
	exit(0);
	tga->file = ft_strjoin2(tga->file, new, 0, repet);
}
