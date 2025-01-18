/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/18 13:35:10 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	ph_rise_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = state;
	pthread_mutex_unlock(&table->stop_lock);
}

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
