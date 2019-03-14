/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:12:34 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/14 10:17:15 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

char	*cut_png_info(char *str)
{
	int		len;

	len = ft_strlen((const char *) str);
	if (len <= 10)
		return (str);
	str += 10;
	if (str[48])
		str[48] = '\0';
	return (str);
}

int		is_space(char c)
{
	if ((c == ' ') || (c == '\n') || (c == '\t'))
		return (1);
	else
		return (0);
}

int		count_space(char *str)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			c++;
		i++;
	}
	return (c);
}

char	*split_space(char *str)
{
	char *dest;
	int i;
	int len;
	int c;

	c = count_space(str);
	len = ft_strlen(str);
	if (!(dest = (char *)malloc(sizeof(char) * (len - c + 1 ))))
		return (NULL);
	i = 0;
	c = 0;
	while (i < len)
	{
		if (!is_space(str[i]))
		{
			dest[c] = str[i];
			c++;
		}
		i++;
	}
	dest[c] = '\0';
	return (dest);
}

int		hex_to_int(char s)
{
	int		dec;

	dec = 0;
	if (s >= 'A' && s <= 'F')
		s -= 55;
	else if (s >= 'a' && s <= 'f')
		s -= 87;
	else
		s -= 48;
	dec = s;
	return (dec);
}

int		hex_to_ascii(char c, char d)
{
	int		high;
	int		low;

	high = hex_to_int(c) * 16;
	low = hex_to_int(d);
	return (high + low);
}

int		hex_to_dec(t_tga tga, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		tga.file[tga.nb_elem] = str[i];
		//printf(" str[%d] = %d ", i,  tga.file[tga.nb_elem]);
		tga.file[tga.nb_elem] = hex_to_ascii(str[i], str[i + 1]);
		tga.nb_elem++;
		i += 2;
	}
	return (0);
}
