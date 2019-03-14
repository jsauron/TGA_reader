/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 07:15:59 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/14 17:16:42 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin2(char *dst, char const *src, size_t len, size_t len2)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	if (!dst || !src)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	printf("malloc size : %lu\n", len + len2 + 1);
	if (!(new = (char *)malloc(sizeof(char) * len + len2 + 1)))
		return (NULL);
	new = ft_strncpy(new, dst, len);
	new = ft_strncpy(&new[len], src, len2);
	new[len + len2] = '\0';
	printf("dst[%p] : %s\n", dst, dst);
	len != 0 ? ft_strdel(&dst) : 0;
	/*size_t onvaatt = -1;
	printf("\nhere");
	while (++onvaatt < (len + len2))
		printf("=> %d ", new[onvaatt]);*/
	printf("new : %s\n\n", new);
	return (new);
}
