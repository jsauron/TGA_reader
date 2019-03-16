/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser_hdr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:01:42 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/16 11:02:58 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	parser_tga(t_tga *tga, unsigned char *hdr)
{
	int i;

	i = 0;
	tga->w = hdr[12] + (hdr[13] * 256); // pas exactement ca mais a revoir 
	tga->h = hdr[14]  + (hdr[15] * 256); // same
	tga->bits_cm = hdr[7];
	tga->color_type = hdr[1];
	tga->compress = hdr[2];
	tga->bitspix = hdr[16];
	tga->cm_begin = hdr[3] + (hdr[4] * 256);
	tga->len_cm = hdr[5] + (hdr[6] * 256);
	tga->alpha = hdr[17];
	printf("w = %d\nh = %d\nbits_cm = %d\ncolor_type = %d\ncompress = %d\nlen_cm = %d\nbit par pix = %d\nalpha = %d\ncm_begin = %d\n",
	tga->w, tga->h, tga->bits_cm, tga->color_type, tga->compress, tga->len_cm,
			tga->bitspix, tga->alpha, tga->cm_begin);
}
