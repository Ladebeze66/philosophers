/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:32:18 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/23 16:22:19 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->eating_mutex);
	time_since_last_meal = get_time(philo->sim->start_time)
		- philo->last_meal_time;
	if (time_since_last_meal <= philo->sim->time_to_die)
	{
		pthread_mutex_unlock(&philo->eating_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->eating_mutex);
	pthread_mutex_lock(&philo->sim->end_mutex);
	if (!philo->sim->is_philosopher_dead)
	{
		philo->sim->is_philosopher_dead = 1;
		pthread_mutex_unlock(&philo->sim->end_mutex);
		print_action(philo, RED"died☠️" RST, 1);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->end_mutex);
	return (0);
}

static int	all_philosophers_have_eaten_required_meals(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		if (sim->philos[i].meals_eaten < sim->max_meals)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	handle_all_philosophers_ate(t_philo *philo)
{
	if (!philo->sim->simulation_end)
	{
		philo->sim->simulation_end = 1;
		printf(RED"ALL PHILOSOPHERS EAT %d MEALS!!"RST"\n",
			philo->sim->max_meals);
		print_action(philo, NULL, 1);
		return (1);
	}
	return (0);
}

static int	check_max_meals(t_philo *philo)
{
	if (philo->sim->max_meals == 0)
	{
		return (0);
	}
	pthread_mutex_lock(&philo->sim->end_mutex);
	if (all_philosophers_have_eaten_required_meals(philo->sim))
	{
		pthread_mutex_unlock(&philo->sim->end_mutex);
		return (handle_all_philosophers_ate(philo));
	}
	pthread_mutex_unlock(&philo->sim->end_mutex);
	return (0);
}

void	*philo_monitor(void *arg)
{
	t_philo	*philo;
	int		dead;
	int		simulation_end;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->sim->end_mutex);
		dead = philo->sim->is_philosopher_dead;
		simulation_end = philo->sim->simulation_end;
		pthread_mutex_unlock(&philo->sim->end_mutex);
		if (dead || simulation_end)
			break ;
		if (check_philosopher_death(philo))
			return (NULL);
		if (check_max_meals(philo))
			return (NULL);
	}
	return (NULL);
}
