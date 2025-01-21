/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 16:46:48 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
Prints specific input error: wrong arguments.
Just wanted to print it with colors, what can I say.
*/
void	ph_arg_error(void)
{
	char	*error;

	error = RED "Invalid arguments." RESET " Please run again with:"
		RED "./philo " RED "number_of_philosophers" MINT "[1-200]"
		RED " time_to_die" MINT "[60-INT_MAX]"
		RED " time_to_eat" MINT "[60-INT_MAX]"
		RED " time_to_sleep" MINT "[60-INT_MAX]"
		RED " [OPTIONAL: number_of_times_each_philosopher_must_eat]"
		MINT "[0-INT_MAX]"
		RESET;
	write(2, error, ph_strlen(error));
}

/*
Starts simulation.
Calls for process creation (fork()) for each philo.
*/
bool	ph_start(t_table *table)
{
	int	i;

	i = 0;
	table->t_start = ph_get_time() + 1000;
	while (i < table->n_philos)
	{
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == 0)
		{
			table->philos[i]->next_meal = table->t_start + table->t_die;
			ph_routine(table->philos[i]);
			exit(0);
		}
		else if (table->philos[i]->pid < 0)
			return (false);
		i++;
		usleep(100);
	}
	return (true);
}

/*
Main function. 
Calls arg checking and parsing.
Calls table init (which inits also philos and semaphores).
Calls simulation start.
Calls monitoring function.
Calls exit function.
*/
int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		ph_arg_error();
		exit(1);
	}
	if (ph_parser(argv))
		exit(1);
	table = ph_init_table(argv);
	if (!table)
		exit(1);
	if (table->max_meals == 0)
		ph_exit(table, 0);
	table->t_start = ph_get_time();
	sem_wait(table->stop_sem);
	if (!ph_start(table))
		ph_exit(table, 1);
	ph_monitor_processes(table);
	sem_wait(table->stop_sem);
	ph_exit(table, 0);
	return (0);
}
