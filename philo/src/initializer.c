/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/18 13:29:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*ph_init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!forks)
		return (ph_error(FORK_INIT_ERR, table), NULL);
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (ph_error(FORK_INIT_ERR, table), NULL);
		i++;
	}
	return (forks);
}

void	ph_give_forks(t_philo *philo)
{
	philo->fork_left = (philo->id - 1) % philo->table->n_philos;
	philo->fork_right = philo->id % philo->table->n_philos;
}

bool	ph_init_mutexes(t_table *table)
{
	table->f_locks = ph_init_forks(table);
	if (!table->f_locks)
		return (false);
	if (pthread_mutex_init(&table->stop_lock, 0) != 0)
	{
		return (ph_error(FLAG_ERR, table), false);
	}
	if (pthread_mutex_init(&table->print_lock, 0) != 0)
		return (ph_error(P_LOCK_ERR, table), false);
	return (true);
}

t_philo	**ph_init_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * table->n_philos);
	if (!philos)
		return (ph_error(MALLOC_ERR, NULL), NULL);
	i = 0;
	while (i < table->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (ph_error(MALLOC_ERR, NULL), NULL);
		if (pthread_mutex_init(&philos[i]->meal_lock, 0) != 0)
			return (ph_error(MEAL_ERR, NULL), NULL);
		philos[i]->table = table;
		philos[i]->id = i + 1;
		philos[i]->meals_eaten = 0;
		ph_give_forks(philos[i]);
		i++;
	}
	return (philos);
}

t_table	*ph_init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (ph_error(MALLOC_ERR, NULL), NULL);
	table->n_philos = ph_atoi(argv[1]);
	table->t_die = ph_atoi(argv[2]);
	table->t_eat = ph_atoi(argv[3]);
	table->t_sleep = ph_atoi(argv[4]);
	if (argv[5])
		table->max_meals = ph_atoi(argv[5]);
	else
		table->max_meals = -1;
	table->philos = ph_init_philos(table);
	if (!table->philos)
		return (NULL);
	if (!ph_init_mutexes(table))
		return (NULL);
	table->stop_flag = false;
	return (table);
}
