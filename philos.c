/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:31:06 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/17 15:05:24 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	if (allocate_memory(sim) < 0)
		return (-1);
	while (i < sim->num_philosophers)
	{
		sim->philos[i].id = i + 1;
		pthread_mutex_init(&sim->forks[i].mutex_fork, NULL);
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1)
			% sim->num_philosophers];
		sim->philos[i].sim = sim;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].can_eat = 0;
		sim->philos[i].last_meal_time = get_time(sim->start_time);
		pthread_mutex_init(&sim->philos[i].eating_mutex, NULL);
		i++;
	}
	init_threads(sim);
	return (0);
}
