/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 16:15:27 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Joins threads before ending execution (cleanup step).
*/
void	ph_join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->n_philos > 1)
		pthread_join(table->observer, NULL);
}

/*
Creates threads and assigns their entry point to ph_routine.
*/
bool	ph_create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				ph_routine, table->philos[i]) != 0)
		{
			ph_error(THREAD_ERR, table);
			return (false);
		}
		i++;
	}
	return (true);
}
