/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:07:22 by abezanni          #+#    #+#             */
/*   Updated: 2018/07/26 13:25:34 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include "vm/vm.h"
#include <fcntl.h>

void	print_memory(const void *addr, size_t size)
{
	unsigned char	*str;
	unsigned char	tabmem[16];
	unsigned char	tab[2];
	size_t			i;
	int				j;

	i = 0;
	j = 0;
	str = (unsigned char *)addr;
	while (i < size)
	{
		tab[0] = *str / 16 < 10 ? *str / 16 + 48 : *str / 16 + 87;
		tab[1] = *str % 16 < 10 ? *str % 16 + 48 : *str % 16 + 87;
		write(1, tab, 2);
		if (i % 2 == 1)
			write(1, " ", 1);
		tabmem[j++] = 31 < *str && *str < 127 ? *str : '.';
		str++;
		i++;
		if (j == 16)
		{
			write(1, tabmem, 16);
			write(1, "\n", 1);
			j = 0;
		}
	}
	if (j != 0)
	{
		while (i % 16 != 0)
		{
			write(1, "  ", 2);
			if (i % 2 == 1)
				write(1, " ", 1);
			i++;
		}
		write(1, tabmem, j);
		write(1, "\n", 1);
	}
}

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
		return (5);
	if (*str == 8)
	{
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

int print_player(char *av, int i)
{
	int				fd;
	char	buf[10000];
	char	*test;
	char	print[4];
	int		ret;
	int		to_print;

	(void)i;
	print[2] = ' ';
	print[3] = 0;
	fd = open(av, O_RDONLY);
	ret = read(fd, buf, 10000);
	test = buf;
	test += 600;
	ret -= 600;
	while (!*test)
	{
		test++;
		ret--;
	}
	while (ret > 0)
	{
		to_print = calc_print((unsigned char *)test);
		if (to_print < 40)
		{
			print_memory(test, to_print);
			test += to_print;
			ret -= to_print;
		}
		else
		{
			print_memory(test, ret);
			ret = 0;
		}
	}
	return (0);
}
