/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:59:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/20 16:42:20 by abezanni         ###   ########.fr       */
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
	size_t			index_line;
	size_t			index_char;
}					t_file;

typedef struct		s_lines{
	char			*str;
	int				num_line;
	struct s_lines	*next;
}					t_lines;

typedef struct		s_elems{
	int				type;
	int				key;
	int				first;
	int				second;
	int				third;
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
	t_lines			*lines;
	t_functions		*functions;
}					t_record;

void	erase(t_record *record);

/*
********************************************************************************
**                                                                            **
**   get_functions.c                                                          **
**                                                                            **
********************************************************************************
*/

void				get_functions(t_record *record, t_lines **current_line,
						t_functions **current_function);

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

char				*search_begin(char *line);
void				get_infos(t_record *record);

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
void				new_t_elem(t_elems **current, int type, int key);

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
**   t_lines.c                                                                **
**                                                                            **
********************************************************************************
*/

void				del_t_line(t_lines **current);
void				del_t_lines(t_lines **current);
void				new_t_line(t_lines **current, char *line, int num);

#endif
