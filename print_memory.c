/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pompedup <pompedup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:07:22 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/01 13:50:16 by pompedup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

int	calc_print(unsigned char *str)
{
	if (*str == 1)
		return (5);
	if (*str == 2)
	{
		if (*(str + 1) == 208)
			return (5);
		return (7);
	}
	if (*str == 3)
	{
		if (*(str + 1) == 80)
			return (4);
		return (5);
	}
	if (*str == 4)
		return (5);
	if (*str == 5)
		return (5);
	if (*str == 6)
	{
		if (*(str + 1) == 84)
			return (5);
		if (*(str + 1) == 116)
			return (6);
		return (8);
	}
	if (*str == 7)
	{
		 if (*(str + 1) == 228)
		 	return (9);
		return (5);
	}
	if (*str == 8)
	{
		 if (*(str + 1) == 228)
		 	return (9);
		if (*(str + 1) == 100)
			return (8);
		return (5);
	}
	if (*str == 9)
		return (3);
	if (*str == 10)
	{
		if (*(str + 1) == 164)
			return (7);
		return (6);
	}
	if (*str == 11)
	{
		if (*(str + 1) == 104)
			return (7);
		if (*(str + 1) == 84)
			return (5);
		return (6);
	}
	if (*str == 12)
		return (3);
	if (*str == 13)
		return (10000);
	return (10000);

}

int main(int ac, char **av)
{
	int				fd;
	unsigned char	buf[10000];
	unsigned char	*test;
	char	print[4];
	int		ret;
	int		to_print;

	print[2] = ' ';
	print[3] = 0;
	fd = open(av[1], O_RDONLY);
	ret = read(fd, buf, 10000);
	test = buf;
	test += 104;
	ret = 100;
	ft_putnbrendl(ret);
	while (!*test)
	{
		test++;
		ret++;
	}
	ft_putnbrendl(ret);
	/*
	while (ret > 0)
	{
		to_print = calc_print(test);
		if (to_print < 40)
		{
			ft_print_memory(test, to_print);
			test += to_print;
			ret -= to_print;
		}
		else
		{
			ft_print_memory(test, ret);
			ret = 0;
		}
	}*/
	return (0);
}
