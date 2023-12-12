/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:54:03 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/17 12:27:25 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_default_values(t_simulation *sim)
{
	sim->num_philosophers = 0;
	sim->time_to_die = 0;
	sim->time_to_eat = 0;
	sim->time_to_sleep = 0;
	sim->max_meals = 0;
	sim->start_time = initialize_start_time();
	sim->is_philosopher_dead = 0;
	sim->simulation_end = 0;
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->end_mutex, NULL);
	return (0);
}

int	args_values(t_simulation *sim, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		pthread_mutex_lock(&sim->print_mutex);
		printf(RED"Usage: %s num_philosophers time_to_die "
			"time_to_eat time_to_sleep [max_meals]\n" RST, argv[0]);
		pthread_mutex_unlock(&sim->print_mutex);
		exit (EXIT_FAILURE);
	}
	else
	{
		sim->num_philosophers = ft_atoi(argv[1]);
		sim->time_to_die = ft_atoi(argv[2]);
		sim->time_to_eat = ft_atoi(argv[3]);
		sim->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
		{
			sim->max_meals = ft_atoi(argv[5]);
		}
	}
	return (0);
}

int	initialize_simulation(t_simulation *sim, int argc, char **argv)
{
	initialize_default_values(sim);
	args_values(sim, argc, argv);
	initialize_philosophers(sim);
	return (0);
}
