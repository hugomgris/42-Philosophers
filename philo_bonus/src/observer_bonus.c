/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/23 11:31:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ph_monitor_processes(t_table *table)
{
	int		status;
	int		finished_philos;
	pid_t	pid;

	finished_philos = 0;
	while (finished_philos < table->n_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			if (WEXITSTATUS(status) == 1)
			{
				ph_end_processes(table);
				sem_post(table->stop_sem);
				break ;
			}
			finished_philos++;
			if (finished_philos == table->n_philos)
			{
				sem_post(table->stop_sem);
				break ;
			}
		}
	}
}

void	*ph_observe(void *arg)
{
	t_philo	*philo;
	time_t	current_time;
	time_t	death_time;

	philo = (t_philo *)arg;
	while (42)
	{
		current_time = ph_get_time();
		death_time = philo->next_meal;
		if (current_time + 1 > death_time)
		{
			sem_wait(philo->table->print_sem);
			current_time = ph_get_time();
			if (current_time > death_time)
			{
				printf("%ld %d died\n",
					death_time - philo->table->t_start, philo->id);
				sem_post(philo->table->stop_sem);
				exit(1);
			}
			sem_post(philo->table->print_sem);
		}
		usleep(10);
	}
	return (NULL);
}
