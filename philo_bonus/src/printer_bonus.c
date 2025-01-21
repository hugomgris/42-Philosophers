/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 17:01:15 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Prints the current status of a philosopher with a timestamp and philosopher ID.
Calculates the elapsed time since the simulation started and formats the output.
The status string is passed as an argument.
*/
#include "../includes/philo_bonus.h"

void	ph_print_status(t_philo *philo, char *status)
{
	printf("%ld %d %s\n", ph_get_time() - philo->table->t_start,
		philo->id, status);
}

/*
Processes and prints the status of a philosopher based on the provided status.
Uses a semaphore to ensure thread-safe printing.
Prints different messages depending on the philosopher's current state.
Releases the semaphore after printing to allow other threads to print.
*/
void	ph_process_status(t_philo *philo, t_status status)
{
	sem_wait(philo->table->print_sem);
	if (status == DEAD)
		ph_print_status(philo, "died");
	else if (status == EATING)
		ph_print_status(philo, "is eating");
	else if (status == SLEEPING)
		ph_print_status(philo, "is sleeping");
	else if (status == THINKING)
		ph_print_status(philo, "is thinking");
	else if (status == GOT_FORK || status == GOT_FORK)
		ph_print_status(philo, "has taken a fork");
	sem_post(philo->table->print_sem);
}
