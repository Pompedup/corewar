/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:27:09 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/05 13:28:12 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main()
{
	int test = 10;
	if ((test += 5) == 10)
		write(1, "coucou\n", 7);
	return (0);
}