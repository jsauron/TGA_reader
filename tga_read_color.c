/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_type_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 11:33:52 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/16 16:02:06 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void	read_color(t_pixel *curr, int bits, unsigned char *file, int pos)
{
	if (bits == 32)
	{
		curr->a = file[pos + 3];
		curr->r = file[pos + 2];
		curr->g = file[pos + 1];
		curr->b = file[pos];
	}
	else if (bits == 24)
	{
		curr->r = file[pos + 2];
		curr->g = file[pos + 1];
		curr->b = file[pos];
	}
	else if (bits == 16 || bits == 15)
	{
		if (bits == 16)
			curr->a = file[pos + 1] & 0x80 ? 255 : 0;
		curr->r = (file[pos + 1] & 0x7C) * 255 / 31;
		curr->g = (file[pos + 1] & 0x3) << 6;
		curr->g += (file[pos] & 0xE0) >> 2;
		curr->b = (file[pos] & 0x1F) * 255 / 31;
	}
	else if (bits  == 8)
	{
		curr->r = file[pos];
		curr->g = file[pos];
		curr->b = file[pos];
	}
}

//void	color_32(t_pixel)
