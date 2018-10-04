/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 23:04:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/04 17:44:09 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft/inc/libft.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 125000

typedef struct	s_lst
{
	int			test;
	struct s_lst	*next;
}				t_lst;

void	create(t_lst **lst, int i)
{
	*lst = malloc(sizeof(t_lst));
	(*lst)->test = i;
	(*lst)->next = 0;
}

int main(int ac, char **av)
{
	t_lst	*test;
	t_lst	**test1;
	int		i;

	i = 0;
	test1 = &test;
	while (i < MAX)
	{
		create(test1, i);
		test1 = &((*test1)->next);
		i++;
	}
	return (0);
}

/*
int main(void)
{
	int tab[MAX];
	int i;

	i = 0;
	while (i < MAX - 1)
	{
		tab[i] = i;
		i++;
	}
	return (0);
}
*/
