/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:35:19 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/16 11:32:05 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

static	void	uncompress_four(t_tga *tga, unsigned char *src, unsigned char *dst)
{
}

static	void	uncompress_three(t_tga *tga, unsigned char *src, unsigned char *dst)
{
}

static	void	uncompress_two(t_tga *tga, unsigned char *src, unsigned char *dst)
{
}

static	void	uncompress_one(t_tga *tga, unsigned char *src, unsigned char *dst)
{
	int		index;

	index = 0;
	while (index < ((tga->bitspix / 8) * tga->w * tga->h))
	{
		if (src[index + 18] < 127)
			dst[index] = src[index + 18];
	}
}

void			rle_uncompress(t_tga *tga)
{
	int					nbyte;

	nbyte = tga->bitspix / 8;
	(tga->result = malloc(sizeof(char) * nbyte * tga->w * tga->h)) == NULL ?
		stop_exec("Malloc failed\n"): 0;
	nbyte == 1 ? uncompress_one(tga, (unsigned char *)tga->str, (unsigned char *)tga->result): 0;
	nbyte == 2 ? uncompress_two(tga, (unsigned char *)tga->str, (unsigned char *)tga->result): 0;
	nbyte == 3 ? uncompress_three(tga, (unsigned char *)tga->str, (unsigned char *)tga->result): 0;
	nbyte == 4 ? uncompress_four(tga, (unsigned char *)tga->str, (unsigned char *)tga->result): 0;
}
