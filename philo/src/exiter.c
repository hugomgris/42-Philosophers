/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/17 17:00:43 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_exit(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->philos[i]->meal_lock);
		pthread_mutex_destroy(&table->f_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->stop_lock);
	ph_cleanup_table(table);
}

void	ph_cleanup_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->f_locks)
		free(table->f_locks);
	if (table->philos)
	{
		i = 0;
		while (i < table->n_philos)
		{
			if (table->philos[i])
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
}

void	ph_error(const char *msg, t_table *table)
{
	if (table)
		ph_cleanup_table(table);
	write(2, msg, ph_strlen(msg));
}
