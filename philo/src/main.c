/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 16:11:23 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
Calls for thread creation.
If there are more than 1 philo, creates the observer thread.
*/
bool	ph_start(t_table *table)
{
	table->t_start = ph_get_time() + (table->n_philos * 2 * 10);
	if (!ph_create_threads(table))
		return (false);
	if (table->n_philos > 1)
	{
		if (pthread_create(&table->observer, NULL, &ph_observer, table) != 0)
		{
			ph_error(THREAD_ERR, table);
			return (false);
		}
	}
	return (true);
}

/*
Main function. 
Calls arg checking and parsing.
Calls table init (which inits also philos).
Calls simulation start.
Calls function that joins threads when simulation ends.
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
		exit (1);
	table = ph_init_table(argv);
	if (table == NULL)
		exit(1);
	if (ph_start(table) == false)
		ph_exit(table, 1);
	ph_join_threads(table);
	ph_exit(table, 0);
	return (0);
}
