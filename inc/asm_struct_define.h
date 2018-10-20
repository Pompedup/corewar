/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_struct_define.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:58:57 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/20 21:14:48 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCT_DEFINE_H
# define ASM_STRUCT_DEFINE_H

# define ELEM_CHRST	" \t\v\n\r\f,"
# define OPTIONS 	"a"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define BLUE		"\033[0;34m"
# define END		"\033[0m"
# define STRR		RED"%s"END
# define STRG		GREEN"%s"END
# define STRB		BLUE"%s"END
# define INTR		RED"%d"END
# define INTG		GREEN"%d"END
# define INTB		BLUE"%d"END
# define FILE		STRB" (line %d): "
# define QUOTER		"\""STRR"\""
# define QUOTEG		"\""STRG"\""
# define QUOTEB		"\""STRB"\""
# define QUOTERC	"\""RED"%c"END"\""
# define QUOTEGC	"\""GREEN"%c"END"\""
# define QUOTEBC	"\""BLUE"%c"END"\""
# define S_DIR		"DIR"
# define S_IND		"IND"
# define USAGE1		"usage: ./data/asm [-a] <sourcefile.s>\n\t-a : Instead of "
# define USAGE2		"creating a .cor file, outputs a stripped and annotated "
# define USAGE3		"version of the code to the standard output\n"
# define USAGE		USAGE1 USAGE2 USAGE3
# define S_REG		"REGISTRE"

/*
********************************************************************************
**                                                                            **
**	Error from file                                                           **
**                                                                            **
********************************************************************************
*/

# define OPEN		STRB": Wrong file name.\n"
# define EMPTY		STRB": This file is empty.\n"
# define READ		STRB": This is not a file.\n"
# define OPENNEW	STRB": Can't create file name %s.\n"
# define WRITEER	STRB": This is not a file.\n"

/*
********************************************************************************
**                                                                            **
**	Error from name or comment                                                **
**                                                                            **
********************************************************************************
*/

# define ENDSECOND	" is declared in the description part.\n"
# define SECOND		FILE"A second "QUOTER ENDSECOND
# define ENDLONG	" (max "INTG" - you "INTR").\n"
# define LONG		FILE"So many characteres for "QUOTER ENDLONG
# define BEGIN		FILE"Missing beginning quote for "QUOTER".\n"
# define ENDING		FILE"Missing ending quote for "QUOTER".\n"
# define ENDAFTER	QUOTER" ("QUOTER").\n"
# define AFTER		FILE"Excess of characteres after the quote of "ENDAFTER
# define BOTH		FILE"Missing "QUOTER" and "QUOTER".\n"
# define ONE		FILE"Missing "QUOTER".\n"
# define CURRENT	" (current : "QUOTER")"

/*
********************************************************************************
**                                                                            **
**	Error from instruction part                                               **
**                                                                            **
********************************************************************************
*/

# define WHAT		FILE"Something go wrong ("QUOTER").\n"
# define NOLABEL	FILE"Missing label name before "QUOTERC".\n"
# define WRLABEL	FILE"Wrong char "QUOTERC" for label "QUOTER".\n"
# define MISSLAB	FILE"Missing LABEL_CHAR "QUOTERC" after label "QUOTER".\n"
# define ENDSPACES	" and LABEL_CHAR "QUOTERC".\n"
# define SPACES		FILE"Space(s) between label "QUOTER ENDSPACES

/*
********************************************************************************
**                                                                            **
**	Error from argument part                                                  **
**                                                                            **
********************************************************************************
*/

# define MISSBEF	FILE"Missing argument before "QUOTERC".\n"
# define MISSSEP	FILE"Missing separator before \"%s\".\n"
# define ENDNBARG	"%s (required "INTG" - you "INTR").\n"
# define MISSARG	FILE"Missing argument for instruction"ENDNBARG
# define TOOMARG	FILE"To many argument for instruction"ENDNBARG
# define TOOMUCH	FILE"Did you forget a "QUOTEGC" before "QUOTER" ?\n"
# define ENDWRARG	" for instruction "STRG".\n"
# define WRARG		FILE QUOTER" is  invalid to the %s position"ENDWRARG

/*
********************************************************************************
**                                                                            **
**	Error from registre part                                                  **
**                                                                            **
********************************************************************************
*/

# define ENDWRREG	"numbers as argument ("STRR").\n"
# define WRREG		FILE"Registre only accepte positif "ENDWRREG
# define BIGREG		FILE"Registre max is 99 ("STRR").\n"
# define ENDREGNEED	" ("GREEN"0 <= x <= 99"END").\n"
# define REGNEED	FILE"Registre need a positif numbers as argument"ENDREGNEED

/*
********************************************************************************
**                                                                            **
**	Error from direct or indirect part                                        **
**                                                                            **
********************************************************************************
*/

# define MISSDIR	FILE"Missing int or label after "QUOTEGC".\n"
# define MISSIND	FILE"Missing int or label after "QUOTEGC".\n"
# define BADDATA 	FILE"Wrong string after "QUOTEGC" ("QUOTER").\n"

/*
********************************************************************************
**                                                                            **
**	Error from direct or indirect part                                        **
**                                                                            **
********************************************************************************
*/

# define GWR		STRB": Creation of "STRG".\n"

# define FUNC		BLUE"\n\nNew Label"END" : ["STRG"]\tAddress : %10d\n"

# define ALLOC		STRB": Allocation error.\n"

# define WREXT		STRR": File name didn't end by "QUOTEG".\n"

# define MISSBGNLAB	FILE"Missing label after \"%c\".\n"

# define NOTNBR		FILE"Wrong char, "QUOTERC" isn't a number ("QUOTER").\n"

# define MISSNBR	FILE"Miss number after \"-\".\n"

# define INTTOOBIG	FILE"Too %s int ("QUOTER").\n"

# define UKLAB		FILE"Unknow label "QUOTER" ("QUOTER").\n"

# define UKARG		FILE"Unknow type of argment "QUOTER".\n"

# define ARGBEFSEP	FILE"Missing arg before separator char.\n"
# define WRTYPE		FILE STRR" is not handle in %s at %s position.\nYou can use"

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
	char			*str;
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
	char			**split;
	t_arg			*args;
	t_bool			complete;
	struct s_elem	*next;
}					t_elem;

typedef struct s_function	t_function;

struct				s_function{
	char			*name;
	int				addr;
	t_elem			*elems;
	t_function		*next;
};

typedef struct		s_record{
	char			*file_name;
	char			*final_name;
	char			name[128];
	t_bool			name_complete;
	char			comment[2052];
	t_bool			comment_complete;
	int				tot;
	t_file			file;
	t_function		*functions;
}					t_record;

#endif
