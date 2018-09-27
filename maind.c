/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maind.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:02:27 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/27 18:46:56 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "inc/asm.h"

int main()
{
	int fd;
	char buf[10];

	if ((fd = open("test_asm", O_WRONLY|O_CREAT, 0666)) == -1)
		printf("Error 1");
	if (write(fd, "coucou les petits", strlen("coucou les petits")) == -1)
		printf("Error 3");
	lseek(fd, SEEK_SET, 0);
	write(fd, "test", 4);
	return (0);
}
