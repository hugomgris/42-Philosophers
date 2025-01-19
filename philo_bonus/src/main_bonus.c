/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/15 12:01:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

int	main(void)
{
	int		i;
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		ph_arg_error();
		exit(1);
	}
	if (ph_parser(argv))
		exit (1);
	table = ph_init_table(argv);
	table->philos = ph_philo_init(table);
	table->t_start = ph_get_time();
	ph_init_sems(table);
	sem_wait(table->stop_sem);
	ph_init_processes(table);
	sem_wait(table->stop_sem);
	ph_cleanup(table);
}
