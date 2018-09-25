/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maind.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:02:27 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 13:08:35 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "inc/asm.h"

int main()
{
	char str[6];
	char str2[6];

	*str = 140;
	*str2 = 250;
	printf("%d\n", ft_strcmp(NULL, str2));
	printf("%d\n", strcmp(NULL, str2));
	return (0);
}
