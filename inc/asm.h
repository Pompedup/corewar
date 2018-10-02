/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:59:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/02 15:33:44 by abezanni         ###   ########.fr       */
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

extern t_op	g_op_tab[];

typedef struct		s_file{
	int				fd;
	char			*line;
	//char			*current;
	size_t			index_line;
	size_t			index_char;
}					t_file;

typedef struct		s_arg{
	int				addr;
	int				type;
	int				value;
	char			*copy;
	int				size;
	t_bool			handled;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_elem{
	int				addr;
	int				size;
	int				type;
	int				key;
	char			*line;
	t_arg			*args;
	t_bool			complete;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_function t_function;

struct				s_function{
	char			*name;
	int				addr;
	t_elem			*elems;
	t_function		*next;
};

typedef struct		s_record{
	char			*name_file;
	char			name[128];
	t_bool			name_complete;
	char			comment[2052];
	t_bool			comment_complete;
	t_file			file;
	t_function		*functions;
}					t_record;

/*
********************************************************************************
**                                                                            **
**   get_dir.c                                                                **
**                                                                            **
********************************************************************************
*/

int		get_dir(t_record *record, t_arg *current_arg, t_elem *elem, int i);

/*
********************************************************************************
**                                                                            **
**   get_elem.c                                                               **
**                                                                            **
********************************************************************************
*/

int		is_label_char(int c);
int		get_elem(t_record *record, t_file *file, t_elem *current_elem);

/*
********************************************************************************
**                                                                            **
**   get_function.c                                                           **
**                                                                            **
********************************************************************************
*/

t_bool	get_function(t_record *record, t_file *file, t_function **current_function);

/*
********************************************************************************
**                                                                            **
**   get_ind.c                                                                **
**                                                                            **
********************************************************************************
*/

int		get_ind(t_record *record, t_arg *current_arg, t_elem *elem, int i);

/*
********************************************************************************
**                                                                            **
**   get_infos.c                                                              **
**                                                                            **
********************************************************************************
*/

t_bool				get_infos(t_record *record, t_file *file);

/*
********************************************************************************
**                                                                            **
**   get_label.c                                                              **
**                                                                            **
********************************************************************************
*/

void	get_label(t_record *record, t_arg *current_arg, char *str, size_t len);

/*
********************************************************************************
**                                                                            **
**   get_reg.c                                                                **
**                                                                            **
********************************************************************************
*/

int		get_reg(t_record *record, t_arg *current_arg, t_elem *elem, int i);

/*
********************************************************************************
**                                                                            **
**   last_verifications.c                                                     **
**                                                                            **
********************************************************************************
*/

t_bool	last_verifications(t_record *record);

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
**   t_elem.c                                                                 **
**                                                                            **
********************************************************************************
*/

void				print_elems(t_elem *current);
void				del_t_elem(t_elem **current);
void				del_t_elems(t_elem **current);
void				new_t_elem(t_elem **current, int type, int addr);

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
**   t_function.c                                                             **
**                                                                            **
********************************************************************************
*/

void				print_functions(t_function *current);
void				del_t_function(t_function **current);
void				del_t_functions(t_function **current);
void				new_t_function(t_function **current, char *name, int pos);

/*
********************************************************************************
**                                                                            **
**   t_arg.c                                                                  **
**                                                                            **
********************************************************************************
*/

void				print_args(t_arg *current);
void				del_t_arg(t_arg **current);
void				del_t_args(t_arg **current);
void				new_t_arg(t_arg **current, int addr);






void	next_comma(t_record *record, t_elem
 *elem);
int	is_label_char(int c);
t_bool	check_authorized_arg(t_record *record, t_elem
 *elem, int arg_type, int indice);
int		verif_synrax(t_record *record, char *str);
void	get_label(t_record *record, t_arg *current_arg, char *str, size_t len);
void	write_file(t_record *record, t_function *functions);

#endif
