/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser_hdr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:01:42 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/14 10:33:06 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	parser_tga(t_tga tga, int *file)
{
	int i;

	i = 0;
	tga.w = file[12] + file[13]; // pas exactement ca mais a revoir 
	tga.h = file[14] + file[15]; // same
	tga.bits_cm = file[7];
	tga.color_type = file[1];
	tga.compress = file[2];
	tga.bitspix = file[16];
	tga.len_cm = file[5] + file[6];
	tga.alpha = file[17];

	printf("\n  w = %d, h = %d, bits_cm = %d, color_type = %d,
			compress = %d, len_cm = %d,  bit par pix = %d, alpha = %d\n",
	tga.w, tga.h, tga.bits_cm, tga.color_type, tga.compress, tga.len_cm,
			tga.bitspix, tga.alpha);
}
