/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 16:49:57 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
Initializes an array of philosopher structures based on n_philo.
Allocates memory for each philosopher and sets their initial values,
	including their ID, meal count, and reference to the table.
If max_meals is set to -1, it indicates that the philosopher should eat forever.
Returns the array of initialized philosophers or NULL if memory allocation fails.
*/
t_philo	**ph_init_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * table->n_philos);
	if (!philos)
		return (ph_error(MALLOC_ERR, NULL), NULL);
	i = 0;
	while (i < table->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (ph_error(MALLOC_ERR, NULL), NULL);
		philos[i]->table = table;
		philos[i]->id = i + 1;
		philos[i]->meals_eaten = 0;
		philos[i]->pid = -1;
		philos[i]->next_meal = 0;
		if (table->max_meals == -1)
			philos[i]->meals_eaten = -1;
		i++;
	}
	return (philos);
}

/*
Initializes semaphores required for the simulation:
	death, printing, stopping, and forks.
Unlinks any existing semaphores with the same names to avoid conflicts.
Creates new semaphores with the specified initial values.
Returns true if all semaphores are successfully created, otherwise returns false.
*/
bool	ph_init_sems(t_table *table)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("forks");
	table->death_sem = sem_open("death", O_CREAT, 0600, 1);
	table->print_sem = sem_open("print", O_CREAT, 0600, 1);
	table->stop_sem = sem_open("stop", O_CREAT, 0600, 1);
	table->forks_sem = sem_open("forks", O_CREAT, 0600,
			table->n_philos);
	if (table->death_sem == SEM_FAILED || table->print_sem == SEM_FAILED
		|| table->stop_sem == SEM_FAILED || table->forks_sem == SEM_FAILED)
		return (false);
	return (true);
}

/*
Initializes the table structure with values parsed from the arguments.
Allocates memory for the table and sets the number of philosophers,
	time to die, time to eat, time to sleep, and max meals.
If the max meals argument is not provided, it defaults to -1 (infinite meals).
Initializes the philosophers and semaphores required for the simulation.
Returns the initialized table or NULL if any initialization step fails.
*/
t_table	*ph_init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (ph_error(MALLOC_ERR, NULL), NULL);
	table->n_philos = ph_atoi(argv[1]);
	table->t_die = ph_atoi(argv[2]);
	table->t_eat = ph_atoi(argv[3]);
	table->t_sleep = ph_atoi(argv[4]);
	if (argv[5])
		table->max_meals = ph_atoi(argv[5]);
	else
		table->max_meals = -1;
	table->philos = ph_init_philos(table);
	table->t_start = ph_get_time();
	if (!ph_init_sems(table))
		return (ph_error(SEM_ERR, NULL), NULL);
	table->stop_flag = NULL;
	return (table);
}
