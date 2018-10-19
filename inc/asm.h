/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:59:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/19 19:18:11 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "common.h"
# include "asm_struct_define.h"

/*
********************************************************************************
**                                                                            **
**   get_arg.c                                                                **
**                                                                            **
********************************************************************************
*/

int		get_reg(t_record *record, t_elem *elem, t_arg *arg, int i);
int		get_dir(t_record *record, t_elem *elem, t_arg *arg, int i);
int		get_ind(t_record *record, t_elem *elem, t_arg *arg, int i);

/*
********************************************************************************
**                                                                            **
**   get_elem.c                                                               **
**                                                                            **
********************************************************************************
*/

int		is_label_char(int c);
t_bool	get_elem(t_record *record, t_elem *current_elem);

/*
********************************************************************************
**                                                                            **
**   get_function.c                                                           **
**                                                                            **
********************************************************************************
*/

t_bool	get_functions(t_record *record, t_file *file,\
	t_function **current_function);

/*
********************************************************************************
**                                                                            **
**   get_infos.c                                                              **
**                                                                            **
********************************************************************************
*/

t_bool	get_infos(t_record *record, t_file *file);

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
**   get_pos.c                                                                **
**                                                                            **
********************************************************************************
*/

t_bool	get_answer(t_record *record, t_elem *elem, t_arg *arg, int erreur);

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

void	error(t_record *record, int error);
void	erase(t_record *record);
t_bool	init(t_record *record, char *file_name);

/*
********************************************************************************
**                                                                            **
**   t_elem.c                                                         struct  **
**                                                                            **
********************************************************************************
*/

void	print_elems(t_elem *current);
void	del_t_elem(t_elem **current);
void	del_t_elems(t_elem **current);
t_bool	new_t_elem(t_record *record, t_elem **current, int type);

/*
********************************************************************************
**                                                                            **
**   t_file.c                                                         struct  **
**                                                                            **
********************************************************************************
*/

void	read_t_file(t_record *record, t_file *file, t_bool info);
void	del_t_file(t_file *file);
void	new_t_file(t_record *record, t_file *file, char *file_name);

/*
********************************************************************************
**                                                                            **
**   t_function.c                                                     struct  **
**                                                                            **
********************************************************************************
*/

void	print_functions(t_function *current);
void	del_t_function(t_function **current);
void	del_t_functions(t_function **current);
t_bool	new_t_function(t_record *record, t_function **current, char *name);

/*
********************************************************************************
**                                                                            **
**   t_arg.c                                                          struct  **
**                                                                            **
********************************************************************************
*/

void	print_args(t_arg *current);
void	del_t_arg(t_arg **current);
void	del_t_args(t_arg **current);
void	new_t_arg(t_arg **current, int addr, char *copy);

/*
********************************************************************************
**                                                                            **
**   verif_elem_str.c                                                  verif  **
**                                                                            **
********************************************************************************
*/

t_bool	verify_elem_str(t_record *record, t_elem *elem);

/*
********************************************************************************
**                                                                            **
**   verif_file_name.c                                                 verif  **
**                                                                            **
********************************************************************************
*/

t_bool	verif_file_name(t_record *record, char *str);

/*
********************************************************************************
**                                                                            **
**   vrite_file.c                                                      write  **
**                                                                            **
********************************************************************************
*/

void	write_file(t_record *record, t_function *functions);

/*
********************************************************************************
**                                                                            **
**   options.c                                                                **
**                                                                            **
********************************************************************************
*/

void	handle_options(t_record *record, int options);
t_bool	handle_args(int ac, char **av, int *options);





t_bool	get_string(t_record *record, t_file *file, t_string *data);
t_bool	get_type(t_record *record, t_file *file, int *type);
t_bool	check_label(t_record *record, t_file *file, char **name);
void	ending_str(char *str);
char	skip_spaces(char **str);
#endif
