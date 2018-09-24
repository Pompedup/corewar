/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:59:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/24 17:10:55 by abezanni         ###   ########.fr       */
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
# define	INVALID_FILE 5

typedef struct		s_file{
	int				fd;
	char			*line;
	char			*current;
	size_t			index_line;
	size_t			index_char;
}					t_file;

typedef struct		s_arg{
	int				type;
	int				value;
	char			*copy;
	t_bool			handled;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_elems{
	int				type;
	int				key;
	t_arg			*args;
	t_bool			complete;
	struct s_elems	*next;
}					t_elems;

typedef struct		s_functions t_functions;

struct				s_functions{
	char			*name;
	int				pos;
	t_elems			*elems;
	t_functions		*next;
};

typedef struct		s_record{
	char			*name;
	char			*comment;
	t_file			file;
	t_functions		*functions;
}					t_record;

/*
********************************************************************************
**                                                                            **
**   check_instruction.c                                                      **
**                                                                            **
********************************************************************************
*/

int		is_label_char(int c);
int		check_elem(t_record *record, t_file *file, t_elems **current_elem, int type);

/*
********************************************************************************
**                                                                            **
**   get_functions.c                                                          **
**                                                                            **
********************************************************************************
*/

void	get_functions(t_record *record, t_file *file, t_functions **current_function);

/*
********************************************************************************
**                                                                            **
**   get_infos.c                                                              **
**                                                                            **
********************************************************************************
*/

void				get_infos(t_record *record, t_file *file);

/*
********************************************************************************
**                                                                            **
**   step.c                                                                   **
**                                                                            **
********************************************************************************
*/

void		error(t_record *record, int error);
void		erase(t_record *record);
void		init(t_record *record, char *file_name);

/*
********************************************************************************
**                                                                            **
**   t_elems.c                                                                **
**                                                                            **
********************************************************************************
*/

void				del_t_elem(t_elems **current);
void				del_t_elems(t_elems **current);
void				new_t_elem(t_elems **current, int type);

/*
********************************************************************************
**                                                                            **
**   t_file.c                                                                 **
**                                                                            **
********************************************************************************
*/

void				read_t_file(t_record *record, t_file *file);
void				del_t_file(t_file *file);
void				new_t_file(t_record *record, t_file *file, char *file_name);

/*
********************************************************************************
**                                                                            **
**   t_functions.c                                                            **
**                                                                            **
********************************************************************************
*/

void				del_t_function(t_functions **current);
void				del_t_functions(t_functions **current);
t_functions			**new_t_function(t_functions **current, char *name, int pos);

/*
********************************************************************************
**                                                                            **
**   t_arg.c                                                                **
**                                                                            **
********************************************************************************
*/

void				del_t_arg(t_arg **current);
void				del_t_arg(t_arg **current);
void				new_t_arg(t_arg **current);

#endif
