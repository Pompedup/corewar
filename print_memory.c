/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:07:22 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/27 16:11:10 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

int	calc_print(unsigned char *str)
{
	unsigned char c;
	if (*str == 1 || *str == 4 || *str == 5)
		return (5);
	if (*str == 9 || *str == 12)
		return (3);
	c = *(str + 1);
	if (c == 80)
		return (4);
	if (c == 84)
		return (5);
	if (c == 100)
		return (8);
	if (c == 104)
		return (7);
	if (c == 108)
		return (9);
	if (c == 112)
		return (5);
	if (c == 116)
		return (6);
	if (c == 124)
		return (11);
	if (c == 144)
		return (7);
	if (c == 164)
		return (11);
	if (c == 208)
		return (5);
	if (c == 228)
		return (9);
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	// if (c == )
	// 	return ();
	if (*str == 13)
		return (10000);
	return (10000);

}

int print_player(char *av, int i)
{
	int				fd;
	unsigned char	buf[10000];
	unsigned char	*test;
	char	print[4];
	int		ret;
	int		to_print;

	(void)i;
	print[2] = ' ';
	print[3] = 0;
	fd = open(av, O_RDONLY);
	ret = read(fd, buf, 10000);
	test = buf;
	test += 800;
	ret -= 800;
	//ft_putnbrendl(ret);
	while (!*test)
	{
		test++;
		ret--;
	}
	//ft_putnbrendl(ret);
	while (ret > 0)
	{
		to_print = calc_print((unsigned char *)test);
		if (to_print < 40)
		{
			ft_print_memory(test, to_print);
			test += to_print;
			ret -= to_print;
		}
		else
		{
			ft_printf("%d\n", ret);
			ft_print_memory(test, ret);
			ret = 0;
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	print_player(av[1], 1);
}
