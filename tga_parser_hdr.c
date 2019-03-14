/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser_hdr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:01:42 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/14 13:46:32 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	parser_tga(t_tga *tga, unsigned char *hdr)
{
	int i;

	i = 0;
	printf("5\n");
	tga->w = (hdr[12] * 256) + hdr[13]; // pas exactement ca mais a revoir 
	tga->h = (hdr[14] * 256) + hdr[15]; // same
	tga->bits_cm = hdr[7];
	tga->color_type = hdr[1];
	tga->compress = hdr[2];
	tga->bitspix = hdr[16];
	tga->len_cm = hdr[5] + hdr[6];
	tga->alpha = hdr[17];
	printf("6\n");

	printf(" \n  w = %d, h = %d, bits_cm = %d, color_type = %d, compress = %d, len_cm = %d,  bit par pix = %d, alpha = %d\n",
	tga->w, tga->h, tga->bits_cm, tga->color_type, tga->compress, tga->len_cm,
			tga->bitspix, tga->alpha);
}
