/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:59:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/02 18:48:50 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "common.h"

# define	YET			-1
# define	OK			0
# define	ALLOC_ERROR	1
# define	NO_FILE		2
# define	CANT_READ	3
# define	WRONG_FORMAT 4

typedef struct		s_lines{
	char			*str;
	int				num_line;
	struct s_lines	*next;
}					t_lines;

typedef struct		s_elems{
	int		type;
	int		key;
	int		first;
	int		second;
	int		third;
	struct s_elems	*next;
}

typedef struct		s_functions t_functions;

struct			s_functions{
	char		*name;
	t_elems		*elems;
	t_functions	*next;
};

typedef struct		s_record{
	char			*name;
	char			*comment;
	t_lines			*lines;
}					t_record;

/*
********************************************************************************
**                                                                            **
**   get_lines.c                                                              **
**                                                                            **
********************************************************************************
*/

int					get_lines(char *file_name, t_lines **lines);

/*
********************************************************************************
**                                                                            **
**   get_infos.c                                                              **
**                                                                            **
********************************************************************************
*/

void				get_infos(t_record *record);

/*
********************************************************************************
**                                                                            **
**   lines.c                                                                  **
**                                                                            **
********************************************************************************
*/

void				delete_t_lines(t_lines **lines);

#endif
