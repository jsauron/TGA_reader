/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_reader_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:08:27 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/14 10:23:51 by jsauron          ###   ########.fr       */
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

int		count_n_malloc(t_tga tga, char *str)
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
	if (!(tga.file = (int *)malloc(sizeof(int ) *  count_line * 16)))
		printf("error malloc\n");
	return (0);
}

int		get_data_tga(t_tga tga, const char *path)
{
	int		fd;
	struct	stat sts;
	char	*str;
	int		i;

	i = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if (fstat(fd, &sts) != 0)
		return (0);
	if (!S_ISREG(sts.st_mode))
		return (0);
	str = hexdump(fd);
	count_n_malloc(tga, str);
	close(fd);
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
	i = 0;
	close(fd);
	return (1);
}

int		tga_load(t_tga tga, const char *path)
{
	get_data_tga(tga, path);
	return (0);
}
