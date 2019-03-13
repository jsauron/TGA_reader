/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_parser_hdr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:01:42 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/13 17:04:32 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	parser_png(t_env *env, int *png)
{
	int i;

	i = 0;
	tga.w = png[12] + png[13]; // pas exactement ca mais a revoir 
	tga.h = png[14] + png[15]; // same
	tga.bits_cm = png[7];
	tga.color_type = png[1];
	tga.compress = png[2];
	tga.bitspix = png[16];
	tga.len_cm = png[5] + png[6];
	tga.alpha = png[17];

	printf("\n  w = %d, h = %d, bits_cm = %d, color_type = %d, compress = %d, len_cm = %d,  bit par pix = %d, alpha = %d\n",
	tga.surface->w, tga.surface->h, tga.bits_cm, tga.color_type, tga.compress, tga.len_cm,
			tga.bitspix, tga.alpha);
}
