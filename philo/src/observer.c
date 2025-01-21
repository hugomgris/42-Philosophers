/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/21 09:44:27 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Checks if the stop flags is risen.
*/
bool	ph_check_simulation_end(t_table *table)
{
	bool	check;

	check = false;
	pthread_mutex_lock(&table->stop_lock);
	if (table->stop_flag == true)
		check = true;
	pthread_mutex_unlock(&table->stop_lock);
	return (check);
}

/*
Sets stop flag (in table struct) to the sent argument value.
*/
void	ph_rise_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = state;
	pthread_mutex_unlock(&table->stop_lock);
}

/*
Kills a philo if it's time to die has come.
This means: time since last meal exceeds time to die.
*/
bool	ph_kill(t_philo *philo)
{
	time_t	time;

	time = ph_get_time();
	if ((time - philo->last_meal_time) >= philo->table->t_die)
	{
		ph_rise_stop_flag(philo->table, true);
		ph_process_status(philo, true, DEAD);
		pthread_mutex_unlock(&philo->meal_lock);
		return (true);
	}
	return (false);
}

/*
Observing loop.
Checks if killing function has taken a life.
Checks if max meals value has been reached by all philos.
The meal mutex is used so that no philo eats after death.
*/
bool	ph_observe(t_table *table)
{
	int		i;
	bool	nourished;

	nourished = true;
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_lock);
		if (ph_kill(table->philos[i]))
			return (true);
		if (table->max_meals != -1)
		{
			if (table->philos[i]->meals_eaten < table->max_meals)
				nourished = false;
		}
		pthread_mutex_unlock(&table->philos[i]->meal_lock);
		i++;
	}
	if (table->max_meals != -1 && nourished == true)
	{
		ph_rise_stop_flag(table, true);
		return (true);
	}
	return (false);
}

/*
Observer thread point of entry.
Makes sure that stop flag is false at start.
Calls observing loop after start delay.
*/
void	*ph_observer(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (table->max_meals == 0)
		return (NULL);
	ph_rise_stop_flag(table, false);
	ph_delay(table->t_start);
	while (42)
	{
		if (ph_observe(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
