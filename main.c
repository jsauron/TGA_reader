/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:08:00 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/14 10:30:06 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_reader.h"

void		stop_exec(char *msg)
{
	ft_putstr(msg);
	exit(0);
}

int main(int argc, char **argv)
{
	t_tga	tga;

	if (argc != 2)
	{
		ft_putstr("Need tga image\n");
		exit(0);
	}
	else
		tga_load(tga, argv[1]);
	return (1);
}
