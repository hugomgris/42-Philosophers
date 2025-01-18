/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/18 13:31:22 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->f_locks[philo->fork_left]);
	ph_process_status(philo, false, GOT_LEFT_FORK);
	pthread_mutex_lock(&philo->table->f_locks[philo->fork_right]);
	ph_process_status(philo, false, GOT_RIGHT_FORK);
	ph_process_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = ph_get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ph_sleep(philo->table, philo->table->t_eat);
	if (ph_check_simulation_end(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	ph_process_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->f_locks[philo->fork_left]);
	pthread_mutex_unlock(&philo->table->f_locks[philo->fork_right]);
	ph_sleep(philo->table, philo->table->t_sleep);
}

void	ph_sleep(t_table *table, time_t t_sleep)
{
	time_t	t_wake;

	t_wake = ph_get_time() + t_sleep;
	while (ph_get_time() < t_wake)
	{
		if (ph_check_simulation_end(table))
			break ;
		usleep(100);
	}
}

void	*ph_one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->f_locks[philo->fork_left]);
	ph_process_status(philo, false, GOT_LEFT_FORK);
	ph_sleep(philo->table, philo->table->t_die);
	ph_process_status(philo, false, DEAD);
	pthread_mutex_unlock(&philo->table->f_locks[philo->fork_left]);
	return (NULL);
}

void	ph_think(t_philo *philo, bool print)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_lock);
	time_to_think = (philo->table->t_die
			- (ph_get_time() - philo->last_meal_time)
			- philo->table->t_eat) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && print == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (print == false)
		ph_process_status(philo, false, THINKING);
	ph_sleep(philo->table, time_to_think);
}

void	*ph_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->max_meals == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = philo->table->t_start;
	pthread_mutex_unlock(&philo->meal_lock);
	ph_delay(philo->table->t_start);
	if (philo->table->t_die == 0)
		return (NULL);
	if (philo->table->n_philos == 1)
		return (ph_one_philosopher(philo));
	else if (philo->id % 2)
		ph_think(philo, true);
	while (ph_check_simulation_end(philo->table) == false)
	{
		ph_eat_and_sleep(philo);
		ph_think(philo, false);
	}
	return (NULL);
}
