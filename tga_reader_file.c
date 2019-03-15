/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:08:27 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/15 14:08:54 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

int			read_hdr(t_tga *tga, int fd)
{
	unsigned char	buff[18];

	read(fd, buff, 18);
	printf("4\n");
	parser_tga(tga, buff);
	return (0);
}

int			read_cm(t_tga *tga, int fd)
{
	unsigned char	buff[tga->len_cm * (tga->bits_cm >> 3)];
	int				i;

	i = -1;
	{
		if (!(tga->colormap = (unsigned char *)malloc(sizeof(unsigned char)
						* tga->len_cm * (tga->bits_cm >> 3))))
			return (0);
		read(fd, buff, (tga->len_cm * (tga->bits_cm >> 3)));
		while (++i < (tga->len_cm * (tga->bits_cm >> 3)))
			tga->colormap[i] = buff[i];
		i = 0;
		while (i < (tga->len_cm * (tga->bits_cm >> 3)))
			printf("%d ", tga->colormap[i++]);
		printf("\n");
	}
	return (1);
}

int			read_data(t_tga *tga, int fd)
{
	unsigned char buff[100];
	int				len;
	int i;

	i = 0;
	if (!(tga->file = (unsigned char *)ft_strdup("")))
		exit(EXIT_FAILURE); // recup error
	while (((len = read(fd, &buff, 100)) > 0))
	{
		if (!(tga->file = (unsigned char *)ft_strjoin2(tga->file, buff, i, len)))
		{
			printf("Error join read_data\n");
			exit(EXIT_FAILURE);
		}
		i += len;
	}
	tga->file[i] = '\n';
	tga->nb_elem = i;
	printf("nb_elem = %d\n", tga->nb_elem);
	return (1);
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
	printf(" size of cm = %d\n", tga->len_cm * (tga->bits_cm >> 3));
	tga->color_type ? read_cm(tga, fd) : 0;
	read_data(tga, fd);
	close(fd);
	return (1);
}

int		tga_load(t_tga *tga, const char *path)
{
	printf("1\n");
	if (get_data_tga(tga, path) == 0)
		printf("not a valid file or path\n");
	/*	int c = 0;
		while (c < tga->nb_elem)
		printf("%d ", tga->file[c++]);
		printf("\n");
		*/
	return (0);
}
