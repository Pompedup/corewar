/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:23:45 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/18 17:44:11 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	missing_name_or_comment(t_record *record, t_file *file)
{
	if (!record->name_complete && !record->comment_complete)
		ft_printf(BOTH, record->file_name, record->file.index_line,
			NAME_CMD_STRING, COMMENT_CMD_STRING);
	else
		ft_printf(ONE, record->file_name, record->file.index_line,\
			!record->name_complete ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	if (file->current)
		ft_printf(CURRENT, file->current);
	ft_printf(".\n");
}

static void	handle_file(t_record *record, int options)
{
	if (get_infos(record, &record->file))
	{
		if (!record->name_complete || !record->comment_complete)
			missing_name_or_comment(record, &record->file);
		else if (get_functions(record, &record->file, &record->functions))
		{
			if (last_verifications(record))
				handle_options(record, options);
		}
	}
}

int			main(int ac, char **av)
{
	t_record	record;
	int			options;
	int			i;

	if (!handle_args(ac, av, &options))
		return (0);
	i = 1;
	while (i < ac)
	{
		if (init(&record, av[i]))
			handle_file(&record, options);
		i++;
		while (i < ac && *av[i] == '-')
			i++;
		erase(&record);
	}
	return (0);
}
