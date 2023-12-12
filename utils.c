/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:21:02 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/17 16:27:28 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *ptr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = - (1);
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * sign);
}

void	print_action(t_philo *philo, char *action, int death_action)
{
	t_simulation	*sim;
	int				is_dead;
	int				all_eat;

	sim = philo->sim;
	pthread_mutex_lock(&sim->print_mutex);
	pthread_mutex_lock(&sim->end_mutex);
	is_dead = sim->is_philosopher_dead;
	all_eat = sim->simulation_end;
	pthread_mutex_unlock(&sim->end_mutex);
	if ((is_dead || all_eat) && !death_action)
	{
		pthread_mutex_unlock(&sim->print_mutex);
		return ;
	}
	if (action)
	{
		printf("%ld ms"YELLOW" %d %s\n", get_time(sim->start_time),
			philo->id, action);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}
