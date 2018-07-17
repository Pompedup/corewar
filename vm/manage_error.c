/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:32:47 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/17 13:51:58 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** file_name is not a corewar executable
*/

/*
** prog number num already used
*/

/*
** file file_name not accessible
*/

/*
** can't perform malloc
*/

void     ft_error(t_corevm *vm, int num_error)
{
    (void)vm;
    (void)num_error;
    printf("eroor %d\n", num_error);
    exit(0);
   // return (0);
}