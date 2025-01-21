/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 17:06:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
Exits the program with the specified exit code.
Performs cleanup of semaphores and table resources before exiting.
*/
time_t	ph_get_time(void)
{
	struct timeval	tv;
	time_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

/*
Terminates all philosopher processes by sending a SIGKILL signal to each process.
Iterates through the philosopher array and kills any process with a valid PID.
*/
void	ph_delay(time_t t_start)
{
	time_t	current_time;

	while (42)
	{
		current_time = ph_get_time();
		if (current_time >= t_start)
			break ;
		if (t_start - current_time > 1)
			usleep(50);
	}
}
