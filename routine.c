/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:20:10 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/23 16:27:02 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eating_mutex);
	if (get_time(philo->sim->start_time)
		- philo->last_meal_time > philo->sim->time_to_die)
	{
		pthread_mutex_unlock(&philo->eating_mutex);
		return ;
	}
	if (!philo->can_eat)
	{
		pthread_mutex_unlock(&philo->eating_mutex);
		return ;
	}
	philo->last_meal_time = get_time(philo->sim->start_time);
	philo->meals_eaten++;
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->eating_mutex);
	usleep(300);
}

void	philo_sleep(t_philo *philo)
{
	philo->can_eat = 0;
	usleep(philo->sim->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	philo->can_eat = 0;
}

void	*philosopher_life(void *arg)
{
	t_philo	*philo;
	int		continue_running;

	philo = (t_philo *)arg;
	continue_running = 1;
	while (continue_running)
	{
		pthread_mutex_lock(&philo->sim->end_mutex);
		continue_running = !philo->sim->is_philosopher_dead
			&& !philo->sim->simulation_end;
		pthread_mutex_unlock(&philo->sim->end_mutex);
		if (!continue_running)
			break ;
		take_forks(philo);
		print_action(philo, GREEN"is eating😋"RST, 0);
		eat(philo);
		release_forks(philo);
		philo->can_eat = 0;
		print_action(philo, ORANGE"is sleeping😴"RST, 0);
		usleep(philo->sim->time_to_sleep * 1000);
		print_action(philo, CYAN"is thinking🤔" RST, 0);
		think(philo);
	}
	return (NULL);
}
