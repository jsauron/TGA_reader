/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 13:54:50 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/13 14:47:11 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_READER_H
# define TGA_READER_H

#include <stdio.h>
#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct s_tga		t_tga;

struct			s_tga
{
	char	*str;
	int		*file;
	int		nb_elem;
	int		w;
	int		h;
	int		bits_cm; //number of bits per palette entry 15,16,24,32
	int				color_type; // type of colour map 0=none, 1=has palette
	int			compress			; //type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
	int			bitspix;  // image bits per pixel 8,16,24,32
	int			alpha;
	int			len_cm;						 // number of colours in palette
};


#endif
