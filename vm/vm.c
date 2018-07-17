/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:57:53 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/17 13:15:51 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "vm.h"

t_champion	*new_champ(char **av, int i)
{
	t_champion	*new;

	if (!(new = malloc(sizeof(t_champion))))
		return (NULL); //mettre le bon message derreur
	if (ft_strcmp(av[i - 2], "-n" && ft_isdigit(av[i - 1]))) // peut etre mettre message derreur si il y a un -n sans digit et inverssement
		new->num = ft_atoi(av[i - 1]);
	//open read le fichier
	// si ft_strlen(de tout le fichier) * 8 > CHAMP_MAX_SIZE
	// le champion est trop gros
	//je sort en freeiant tout
	return (new);	
}*/ 

/*
** on cree les champions (et les trier dans lordre de num)
*/
/*int		register_champions(char **av, t_corevm *vm)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!(vm->players = malloc(sizeof(t_champion) * vm->nb_champion + 1)))
		return (0); //mettre le bon message derreur
	vm->players[vm->nb_champion] = NULL;
	while (av[i])
	{
		while (!ft_strstr(av[i], ".cor\0"))
			i++;
		vm->players[j] = new_champ(av, i);
		vm->players[j]->pc = 0; //pour le moment (faut faire le calcul) num champ / total champ
	}
	return (1);	
}*/
