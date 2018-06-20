/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:57:53 by ccoupez           #+#    #+#             */
/*   Updated: 2018/06/20 19:03:56 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_champion	*new_champ(char **av, int i)
{
	t_champion	*new;

	if (!(new = malloc(sizeof(t_champion))))
		return (NULL); //mettre le bon message derreur
	if (ft_strcmp(av[i - 2], "-n" && ft_isdigit(av[i - 1]))) // peut etre mettre message derreur si il y a un -n sans digit et inverssement
		new->num = ft_atoi(av[i - 1])
	//open le fichier
	// le lire avec un buffer de taille CHAMP_MAX_SIZE + 1
	// si je peut lire encore un truc cest que cest trop grand
	//je sort en freeiant tout
}

/*
** on cree les champions (et les trier dans lordre de num)
*/
int		register_champions(char **av, t_vm *vm)
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
		vm->players[j]->pc = 0; //pour le moment (faut faire le calcul)
		
	}
	return (1);	
}

/*
** on init la vm avec le nombre de champion le nombre de cycle
** et avec lallocation de la memoire de la vm a MEM_SIZE
*/

int     init_vm(char **av, t_vm *vm)
{
	int     i;

	i = 1;
	vm->nb_cycles = 0;
	vm->nb_champion = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], "-dump") && ft_isdigit(av[i + 1]))
			vm->nb_cycles = ft_atoi(av[++i]);
		if (ft_strstr(av[i], ".cor\0"))
			vm->nb_champion++;
		i++;
	}
	if (vm->nb_champion < 2 || vm->nb_cycles < 1) // a voir pour ca vm->nb_cycles < 1
		return (0); // il ny a pas ou quun champion
	register_champions(av, vm);
	if (!(vm->core = malloc(sizeof(char) * MEM_SIZE)))
		return (0);
	return (1);
}

int     main(int ac, char **av)
{
    t_vm    vm;

    if (!init_vm(av, &vm))
        return (-1); // ft_error
    return (0);
}