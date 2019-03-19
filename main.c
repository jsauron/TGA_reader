/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:08:00 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/19 13:50:58 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void		stop_exec(char *msg)
{
	ft_putstr(msg);
	exit(0);
}

int		get_data_tga(t_tga *tga, const char *path)
{
	int		fd;
	struct	stat sts;
	int		i;

	i = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if (fstat(fd, &sts) != 0)
		return (0);
	if (!S_ISREG(sts.st_mode))
		return (0);
	read_hdr(tga, fd);
	printf("size of cm = %d\n", tga->len_cm * (tga->bits_cm >> 3));
	tga->compress ? 0 : printf("pas de donne image");
	tga->color_type ? read_cm(tga, fd) : 0;
	read_data(tga, fd);
	close(fd);
	return (1);
}

int		tga_load(t_tga *tga, const char *path)
{
	if (get_data_tga(tga, path) == 0)
		printf("not a valid file or path\n");
	int c = 0;
	  while (c < tga->nb_elem)
	  printf("%d ", tga->file[c++]);
	  printf("\n");
	if (tga->compress >= 8)
	{
		printf("RLE file\n");
		rle_uncompress(tga);
	}
	create_pxl(tga);
	return (0);
}

int main(int argc, char **argv)
{
	t_tga	*tga;

	if (argc != 2)
	{
		ft_putstr("Need tga image\n");
		exit(0);
	}
	else
	{
		if(!(tga = (t_tga *)malloc(sizeof(t_tga))))
			return (0);
		tga_load(tga, argv[1]);
	}
	printf("la\n");
	int i = 0;
	while (i < tga->w * tga->h)
	{
		printf("A[%d] R[%d] G[%d] B[%d] %d\n", tga->pxl[i].a, tga->pxl[i].r,  tga->pxl[i].g,  tga->pxl[i].b, i);
	i++;
	}
	return (1);
}
