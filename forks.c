/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:50:15 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/23 16:09:52 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	print_action(philo, BLUE"has taken a fork🍴"RST, 0);
	while (1)
	{
		pthread_mutex_lock(&philo->sim->end_mutex);
		if (philo->sim->is_philosopher_dead)
		{
			pthread_mutex_unlock(&philo->sim->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->end_mutex);
	}
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->sim->num_philosophers == 1)
	{
		single_philosopher(philo);
		return ;
	}
	usleep(300);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		print_action(philo, BLUE"has taken a fork🍴"RST, 0);
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		print_action(philo, BLUE"has taken a fork🍴"RST, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		print_action(philo, BLUE"has taken a fork🍴"RST, 0);
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		print_action(philo, BLUE"has taken a fork🍴"RST, 0);
	}
	philo->can_eat = 1;
}

void	release_forks(t_philo *philo)
{
	if (philo->can_eat)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		if (philo->sim->num_philosophers > 1)
		{
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		}
		philo->can_eat = 0;
	}
	usleep(300);
}
