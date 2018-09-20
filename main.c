/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 23:04:59 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/20 15:21:40 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

int main()
{
	//int tab[] = { 1 , 3 , 4 , 10, 15, 16, 20, 28, 56};
	//ft_print_memory(tab, 36);

	unsigned char test[] = "coucou";
	unsigned char *test2;
	unsigned short test3;
	unsigned short *test4;

	test2 = test + 2;
	test3 = (test2[0] << 8) + test2[1];
	printf("%x\n", test[2]);
	printf("%x\n", test[3]);
	printf("%x\n", test3);
	test4 = test + 2;
	printf("%p\n", test4);
	printf("%x\n", *test4);
	return (0);
}
