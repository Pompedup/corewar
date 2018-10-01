/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:43:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/28 16:26:09 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

int main()
{
	char *buf;
	int fd = open("test.cor", O_RDONLY);
	buf = malloc(200);
	read(fd, buf, 200);
	buf += 136;
	write(1, buf, 4);
	free(buf - 136);
	return (0);
}
/*
4 magic
128 + 4
4 reg prog size
2048 + 4*/
