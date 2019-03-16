/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 13:54:50 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/16 11:43:54 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_READER_H
# define TGA_READER_H

#include <stdio.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/stat.h>

typedef struct	s_pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	struct s_pixel	*next;
	struct s_pixel	*bf;
}				t_pixel;

typedef struct	s_tga
{
	t_pixel		*cm;
	t_pixel		*pxl;
	char		*str;
	char		*result;
	unsigned char	*colormap;
	unsigned char	*file;
	int			nb_elem;
	int			cm_begin;
	int			w;
	int			h;
	int			bits_cm;	//number of bits per palette entry 15,16,24,32
	int			color_type; // type of colour map 0=none, 1=has palette
	int			compress; 	//type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
	int			bitspix;	// image bits per pixel 8,16,24,32
	int			alpha;
	int			len_cm;		// number of colours in palette
}				t_tga;

//rle.c
void			stop_exec(char *msg);
void			rle_uncompress(t_tga *tga);
//tga_parser_hdr.c
void			parser_tga(t_tga *tga, unsigned char *hdr);
// tga_reader_file.c
char			*hexdump(int fd);
int				count_n_malloc(t_tga *tga, char *str);
int				get_data_tga(t_tga *tga, const char *path);
int				tga_load(t_tga *tga, const char *path);
int				read_hdr(t_tga *tga, int fd);
int				get_data_tga(t_tga *tga, const char *path);
//utils.c
char	*cut_png_info(char *str);
int		is_space(char c);
int		count_space(char *str);
char	*split_space(char *str);
int		hex_to_int(char s);
int		hex_to_ascii(char c, char d);
int		hex_to_dec(t_tga *tga, char *str);
//lstpxl.c
void	fill_maillon(t_tga *tga, t_pixel *curr, int maillon, int mode);
void	create_maillon(t_pixel *curr);
void	fill_lst(t_tga *tga, t_pixel *cm, int mode);
void	init_lst(t_pixel *pxl);
void	create_lst(t_tga *tga);
//set_pxl_color.c
void	fill_value(t_pixel *pxl, t_pixel *pos);
void	fill_pxl(t_tga *tga, t_pixel *pxl);
void	range_pxl(t_tga *tga);
//tga_type_read.c
void	read_color(t_pixel *curr, int bits, unsigned char *file, int pos);
#endif
