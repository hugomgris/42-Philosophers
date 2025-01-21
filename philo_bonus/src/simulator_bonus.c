/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 17:03:03 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
Handles the eating process for a philosopher.
Calculates the start and end times of the eating period.
Updates the philosopher's next meal time and increments the meal count.
If the philo has eaten the maximum number of meals, releases forks and exits.
Releases the forks after eating to allow other philosophers to use them.
*/
void	ph_eat(t_philo *philo)
{
	time_t	start_time;
	time_t	end_time;

	start_time = ph_get_time();
	philo->next_meal = start_time + philo->table->t_die;
	end_time = start_time + philo->table->t_eat;
	ph_process_status(philo, EATING);
	philo->meals_eaten++;
	ph_delay(end_time);
	if (philo->table->max_meals != -1
		&& philo->meals_eaten >= philo->table->max_meals)
	{
		sem_post(philo->table->forks_sem);
		sem_post(philo->table->forks_sem);
		exit(0);
	}
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}

/*
Handles the sleeping process for a philosopher.
Calculates the end time of the sleeping period.
Prints the sleeping status and delays until the sleeping period is over.
*/
void	ph_sleep(t_philo *philo)
{
	time_t	end_time;

	end_time = ph_get_time() + philo->table->t_sleep;
	ph_process_status(philo, SLEEPING);
	ph_delay(end_time);
}

/*
Handles the process of a philosopher picking up forks.
Uses semaphores to lock the forks and prints the status when a fork is taken.
Ensures that the philosopher picks up both forks before proceeding.
*/
void	ph_take_fork(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	ph_process_status(philo, GOT_FORK);
	sem_wait(philo->table->forks_sem);
	ph_process_status(philo, GOT_FORK);
}

/*
Main routine for each philosopher thread.
Delays the start to synchronize with the simulation start time.
Creates and detaches an observer thread to monitor the philosopher's state.
Alternates between taking forks, eating, sleeping, and thinking in a loop.
*/
void	ph_routine(t_philo *philo)
{
	pthread_t	observer;

	ph_delay(philo->table->t_start);
	pthread_create(&observer, NULL, ph_observe, philo);
	pthread_detach(observer);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (42)
	{
		ph_take_fork(philo);
		ph_eat(philo);
		ph_sleep(philo);
		ph_process_status(philo, THINKING);
	}
}
