/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:58:09 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/03 18:05:54 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *test(char *teste)
{
	char test[20] = "coucoucoucou";
	memcpy(teste, test, sizeof(test));
	printf("\n");
	return (test);
}

int main()
{
	static char *teste;
	int i = 10;
	while (i--)
	{
		if (!teste)
		{
			teste = malloc(20);
			test(teste);
			printf("%s\n", teste);
		}
			printf("dfdsfs\n");
	}
	return (0);
}
