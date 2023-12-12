/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:45:37 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/17 11:48:26 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_memory(t_simulation *sim)
{
	sim->forks = ft_calloc(sim->num_philosophers, sizeof(t_fork));
	if (!sim->forks)
		return (-1);
	sim->philos = ft_calloc(sim->num_philosophers, sizeof(t_philo));
	if (!sim->philos)
	{
		free(sim->forks);
		return (-1);
	}
	return (0);
}

void	cleanup(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex_fork);
		pthread_mutex_destroy(&sim->philos[i].eating_mutex);
		i++;
	}
	free(sim->philos);
	free(sim->forks);
	pthread_mutex_destroy(&sim->end_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
}
