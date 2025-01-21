/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 17:06:12 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
Exits the program with the specified exit code.
Performs cleanup of semaphores and table resources before exiting.
*/
void	ph_exit(t_table *table, int code)
{
	ph_cleanup_semaphores(table);
	ph_cleanup_table(table);
	exit(code);
}

/*
Terminates all philosopher processes by sending a SIGKILL signal to each process.
Iterates through the philosopher array and kills any process with a valid PID.
*/
void	ph_end_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (table->philos[i]->pid > 0)
			kill(table->philos[i]->pid, SIGKILL);
		i++;
	}
}

/*
Cleans up and closes all semaphores used in the simulation.
Unlinks the semaphores to ensure they are properly removed from the system.
*/
void	ph_cleanup_semaphores(t_table *table)
{
	sem_close(table->death_sem);
	sem_close(table->print_sem);
	sem_close(table->stop_sem);
	sem_close(table->forks_sem);
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("forks");
}

/*
Cleans up and frees all dynamically allocated memory
	for the table and philosophers.
Frees the array of philosopher structures and the table itself.
*/
void	ph_cleanup_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
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
Handles errors by printing an error message and performing cleanup
	if a table is provided.
Writes the error message to standard error and cleans up the table resources.
*/
void	ph_error(const char *msg, t_table *table)
{
	if (table)
		ph_cleanup_table(table);
	write(2, msg, ph_strlen(msg));
}
