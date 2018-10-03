/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 23:04:59 by pompedup          #+#    #+#             */
/*   Updated: 2018/10/03 15:28:38 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include <stdio.h>

#define MAX 10000

int main(int ac, char **av)
{
	char buf[MAX];
	char buf2[MAX];
	int fd;
	int fd2;
	int ret;
	int ret2;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	ret = read(fd, buf, MAX);
	ret2 = read(fd2, buf2, MAX);
	if (ret != ret2)
		ft_printf("Error -> First : %d - Second : %d\n", ret, ret2);
	if (ft_memcmp(buf, buf2, ret2))
		ft_printf("DIIIIFFFFF");
	return (0);
}
