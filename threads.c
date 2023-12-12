/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:45:20 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/23 16:28:10 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philosopher_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		if (i % 2 == 0)
			pthread_create(&sim->philos[i].thread, NULL,
				philosopher_life, &sim->philos[i]);
		else
			pthread_create(&sim->philos[i].thread, NULL,
				philosopher_life, &sim->philos[i]);
		i++;
	}
	return (1);
}

static int	create_monitoring_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		if (i % 2 == 0)
			pthread_create(&sim->philos[i].philosopher_monitor, NULL,
				philo_monitor, &sim->philos[i]);
		else
			pthread_create(&sim->philos[i].philosopher_monitor, NULL,
				philo_monitor, &sim->philos[i]);
		i++;
	}
	return (1);
}

int	init_threads(t_simulation *sim)
{
	if (!create_philosopher_threads(sim))
		return (0);
	if (!create_monitoring_threads(sim))
		return (0);
	return (1);
}

int	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philos[i].philosopher_monitor, NULL);
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	return (1);
}
