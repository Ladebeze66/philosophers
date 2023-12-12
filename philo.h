/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:44:03 by fgras-ca          #+#    #+#             */
/*   Updated: 2023/10/23 16:29:16 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define RST   		"\033[0;39m"
# define GRAY		"\033[0;90m"
# define RED		"\033[0;91m"
# define GREEN		"\033[0;92m"
# define YELLOW		"\033[0;93m"
# define BLUE		"\033[0;94m"
# define MAGENTA	"\033[0;95m"
# define CYAN		"\033[0;96m"
# define WHITE		"\033[0;97m"
# define ORANGE		"\033[38;5;214m"

typedef struct s_simulation	t_simulation;

typedef struct s_fork
{
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				can_eat;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_t		philosopher_monitor;
	pthread_mutex_t	eating_mutex;
	t_simulation	*sim;
}	t_philo;

typedef struct s_simulation
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long			start_time;
	t_philo			*philos;
	t_fork			*forks;
	volatile int	is_philosopher_dead;
	volatile int	simulation_end;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
}	t_simulation;

int		initialize_simulation(t_simulation *sim, int argc, char **argv);
int		initialize_philosophers(t_simulation *sim);
int		ft_atoi(const char *nptr);
int		init_threads(t_simulation *sim);
int		join_threads(t_simulation *sim);
int		args_values(t_simulation *sim, int argc, char **argv);
int		initialize_default_values(t_simulation *sim);
int		allocate_memory(t_simulation *sim);
long	initialize_start_time(void);
long	get_time(long start_time);
void	*philosopher_life(void *arg);
void	cleanup(t_simulation *sim);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	print_action(t_philo *philo, char *action, int death_action);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	*philo_monitor(void *arg);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
