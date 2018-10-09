/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:59:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/09 18:03:31 by abezanni         ###   ########.fr       */
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

# define	RED		"\033[1;31m"
# define	GREEN	"\033[1;32m"
# define	BLUE	"\033[1;34m"
# define	END		"\033[0m"
# define	STRR	RED"%s"END
# define	STRG	GREEN"%s"END
# define	STRB	BLUE"%s"END
# define	INTR	RED"%d"END
# define	INTG	GREEN"%d"END
# define	INTB	BLUE"%d"END
# define	FILE	STRB" (line %d): "
# define	QUOTER	"\""STRR"\""
# define	QUOTEG	"\""STRG"\""
# define	QUOTEB	"\""STRB"\""
# define	QUOTEC	"\""RED"%c"END"\""

/*
********************************************************************************
**                                                                            **
**	Error from file                                                           **
**                                                                            **
********************************************************************************
*/

# define	OPEN	STRB": Wrong name.\n"
# define	EMPTY	STRB": This file is empty.\n"
# define	READ	STRB": This is not a file.\n"

/*
********************************************************************************
**                                                                            **
**	Error from name or comment                                                **
**                                                                            **
********************************************************************************
*/

# define	SECOND	FILE"A second "QUOTER" is declared in the description part.\n"
# define	LONG	FILE"So many characteres for "QUOTER" (max "INTG" - you "INTR").\n"
# define	BEGIN	FILE"Missing beginning quote for "QUOTER".\n"
# define	ENDING	FILE"Missing ending quote for "QUOTER".\n"
# define	AFTER	FILE"Excess of characteres after the quote of "QUOTER" ("QUOTER").\n"
# define	BOTH	FILE"Missing "QUOTER" and "QUOTER".\n"
# define	ONE		FILE"Missing "QUOTER".\n"
# define	CURRENT " (current : "QUOTER")"

/*
********************************************************************************
**                                                                            **
**	Error from instruction part                                               **
**                                                                            **
********************************************************************************
*/

# define	WHAT	FILE"Something go wrong ("QUOTER").\n"
# define	NOLABEL	FILE"Missing label name before "QUOTEC".\n"
# define	WRLABEL	FILE"Wrong char "QUOTEC" for label "QUOTER".\n"
# define	MISSLAB	FILE"Missing LABEL_CHAR "QUOTEC" after label "QUOTER".\n"
# define	SPACES	FILE"Space(s) between label "QUOTER" and LABEL_CHAR "QUOTEC".\n"


# define	MISSBEF	FILE"Missing argument before "QUOTEC".\n"
# define	MISSBET	FILE"Missing argument before "QUOTEC".\n"
# define	MISSARG	FILE"Missing argument for instruction NAMEG (required "INTG" - you "INTR").\n"
# define	WRARG	FILE QUOTER" is  invalid to the %s position for instruction "STRG".\n"


# define	WRREG	FILE"Registre only accepte positif numbers as argument ("STRR").\n"
# define	BIGREG	FILE"Registre max is 99 ("STRR").\n"
//column
# define	ALLOC	STRB": Allocation error.\n"

extern t_op	g_op_tab[];

typedef struct		s_string
{
	int				max;
	int				size;
	int				index_line;
	char			*addr;
	char			*type;
}					t_string;

typedef struct		s_file{
	int				fd;
	char			*line;
	char			*current;
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
	int				index_line;
	t_op			op_case;
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
	int				tot;
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
t_bool		get_elem(t_record *record, t_file *file, t_elem *current_elem);

/*
********************************************************************************
**                                                                            **
**   get_function.c                                                           **
**                                                                            **
********************************************************************************
*/

t_bool	get_functions(t_record *record, t_file *file, t_function **current_function);

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
t_bool		init(t_record *record, char *file_name);

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
t_bool				new_t_elem(t_record *record, t_elem **current, int type);

/*
********************************************************************************
**                                                                            **
**   t_file.c                                                                 **
**                                                                            **
********************************************************************************
*/

void				read_t_file(t_record *record, t_file *file, t_bool info);
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
t_bool				new_t_function(t_record *record, t_function **current, char *name);

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






t_bool	next_comma(t_record *record, t_elem *elem, t_bool first);
int	is_label_char(int c);
t_bool	check_authorized_arg(t_record *record, t_elem
 *elem, int arg_type, int indice);
int		verif_synrax(t_record *record, char *str);
void	get_label(t_record *record, t_arg *current_arg, char *str, size_t len);
void	write_file(t_record *record, t_function *functions);
t_bool	get_string(t_record *record, t_file *file, t_string *data);
t_bool		get_type(t_record *record, t_file *file, int *type);
t_bool		check_label(t_record *record, t_file *file, char **name);
#endif
