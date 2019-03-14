/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:08:27 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/14 17:20:50 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

char	*hexdump(int fd)
{
	char	buf[16];
	int		stored;
	int		i;
	int		j;
	char	*str[10000];

	j = 0;
	while ((stored = read(fd, &buf, 16)) > 0)
	{
		i = 0;
		if (stored == 16)
		{
			while (i < 16)
				sprintf(str[j], "%.2hhx", buf[i++]);
		}
		else
		{
			while (--stored >= 0)
				sprintf(str[j], "%.2hhx", buf[i++]);
		}
		j++;
		printf("\n");
	}
	return ((stored != -1) ? *str : NULL);
}

/*int		count_n_malloc(t_tga tga, char *str)
{
	int		c;
	int		i;
	int		count_line;
	char	buff;

	count_line = 0;
	i = 0;
	while (str[i])
	{
		c == 0 ? count_line++ : count_line;
		c = 1;
		c = (buff == '\n') ? 0 : c;
		i++;
	}
	if (!(tga.file = (char *)malloc(sizeof(char ) *  count_line * 16)))
		printf("error malloc\n");
	ft_strcpy(tga.file, (const char)str);
	return (0);
}*/

int			read_hdr(t_tga *tga, int fd)
{
	unsigned char	buff[18];

	read(fd, buff, 18);
	printf("3\n");
	printf("buff = %d\n", buff[12]);
	printf("4\n");
	parser_tga(tga, buff);
	return (0);
}

int			read_data(t_tga *tga, int fd)
{
	unsigned char buff[100];
	unsigned char *str;
	int				len;
	int i;

	//str = NULL;
	i = 0;
	if (!(str = (unsigned char *)ft_strdup("")))
		exit(EXIT_FAILURE); // recup error
	while (((len = read(fd, &buff, 100)) > 0))
	{
		if (!(str = (unsigned char *)ft_strjoin2(
		(char *)str, (char const *)buff, i, len)))	
		{
			printf("Error join read_data\n");
			exit(EXIT_FAILURE);
		}
		ft_bzero(&buff, sizeof(100));
		i += len;
	}

	printf("OK TO CONTINUE\n");
	////////////////////////

	printf("\n9\n");
	printf("i = %d\n", i);
	if (!(tga->file = (unsigned char *)malloc(sizeof(unsigned char ) * i + 1)))
		return (0);
	printf("10\n");
	int c = 0;
	while (c < i)
	{
		tga->file[c] = str[c];
	//	printf("%d ", tga->file[c]);
		c++;
	}
	tga->file[c] = '\n';
	c = 0;
//	while (c < i)
//		printf("%d ", tga->file[c++]);
//	printf("\n");
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
	printf("2\n");
	read_hdr(tga, fd);
	read_data(tga, fd);
	close(fd);
/*	count_n_malloc(tga, str);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &str) > 0)
	{
		if (ft_strlen((const char *) str) > 10)
			hex_to_dec(tga, split_space(cut_png_info(str)));
		free(str);
		i++;
	}
	tga.file[tga.nb_elem] = -1;
	*/
	return (1);
}

int		tga_load(t_tga *tga, const char *path)
{
	printf("1\n");
	if (get_data_tga(tga, path) == 0)
		printf("not a valid file or path\n");
	return (0);
}
