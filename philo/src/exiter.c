/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 17:04:40 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Exits the program with the specified exit code.
Performs cleanup of mutexes and table resources before exiting.
*/
void	ph_exit(t_table *table, int code)
{
	ph_cleanup_mutexes(table);
	ph_cleanup_table(table);
	exit(code);
}

/*
Cleans up and destroys all mutexes used in the simulation.
Iterates through the fork locks and meal locks for each philosopher,
	destroying them.
Destroys the print and stop locks used for synchronization.
*/
void	ph_cleanup_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->f_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->stop_lock);
}

/*
Cleans up and frees all dynamically allocated memory
	for the table and philosophers.
Frees the array of fork locks, the array of philosopher structures,
	and the table itself.
*/
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

/*
Handles errors by printing an error message and
	performing cleanup if a table is provided.
Writes the error message to standard error and cleans up the table resources.
*/
void	ph_error(const char *msg, t_table *table)
{
	if (table)
		ph_cleanup_table(table);
	write(2, msg, ph_strlen(msg));
}
