/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tettre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:56:01 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/24 16:05:16 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main()
{
	char *test;
	char *anepaschanger;
	char *coucou;
	int i = 0;
	test = malloc(10);
	anepaschanger = malloc(10);
	coucou = malloc(10);
	printf("%p\n%p\n%p\n", test, anepaschanger, coucou);
	printf("1)\n%s\n%s\n%s\n", test, anepaschanger, coucou);
	while (i < 10)
		test[i++] = 'a';
	i = 0;
	while (i < 10)
		coucou[i++] = i < 5 ? 'b' : 'c';
	printf("2)\n%s\n%s\n%s\n", test, anepaschanger, coucou);
	test[6] = 0;
	strcat(test, coucou);
	strcat(test, coucou);
	printf("3)\n%s\n%s\n%s\n", test, anepaschanger, coucou);
	free(test);
	printf("3)\n%s\n%s\n%s\n", test, anepaschanger, coucou);
	free(coucou);
	printf("3)\n%s\n%s\n%s\n", test, anepaschanger, coucou);
	return (0);
}
