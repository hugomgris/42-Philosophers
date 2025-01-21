/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:12:29 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/20 16:57:12 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
Checks if the number of philosophers is valid.
Converts the input string to an integer and ensures it is within 1 to 200.
Prints an error message if the number of philosophers is invalid.
Returns 1 if the input is invalid, otherwise returns 0.
*/
int	ph_check_philos(char *philos)
{
	int		value;
	char	*error;

	value = ph_atoi(philos);
	if (value <= 0)
	{
		error = "Error: at least 1 philosopher needed\n";
		write(2, error, ph_strlen(error));
		return (1);
	}
	if (value > 200)
	{
		error = "Error: maximum of 200 philosophers is allowed\n";
		write(2, error, ph_strlen(error));
		return (1);
	}
	return (0);
}

/*
Checks if the time values for dying, eating, and sleeping are valid.
Converts the input strings to integers and ensures they are +60 ms.
Prints an error message if any time value is invalid.
Returns 1 if any input is invalid, otherwise returns 0.
*/
int	ph_check_times(char *die, char *eat, char *sleep)
{
	int		t_die;
	int		t_eat;
	int		t_sleep;
	char	*error;

	t_die = ph_atoi(die);
	t_eat = ph_atoi(eat);
	t_sleep = ph_atoi(sleep);
	if (t_die < 0 || t_eat < 0 || t_sleep < 0)
	{
		error = "Error: times need to be positive and between 60 and INT_MAX\n";
		write(2, error, ph_strlen(error));
		return (1);
	}
	if (t_die < 60 || t_eat < 60 || t_sleep < 60)
	{
		error = "Error: times must be at least 60 ms\n";
		write(2, error, ph_strlen(error));
		return (1);
	}
	return (0);
}

/*
Checks if the number of meals is valid.
Converts the input string to an integer and ensures it is non-negative.
Prints an error message if the number of meals is invalid.
Returns 1 if the input is invalid, otherwise returns 0.
*/
int	ph_check_meals(char *meals)
{
	int		n_meals;
	char	*error;

	n_meals = ph_atoi(meals);
	if (n_meals < 0)
	{
		error = "Error: meals arg needs to be positive"
			" and between 0 and INT_MAX\n";
		write(2, error, ph_strlen(error));
		return (1);
	}
	return (0);
}

/*
Checks if the command-line arguments contain only numeric values.
Iterates through the arguments and verifies that each one is a valid number.
Prints an error message if any argument contains non-numeric characters.
Returns 1 if any argument is invalid, otherwise returns 0.
*/
int	ph_check_syntax(char **argv)
{
	int		i;
	char	*error;

	i = 0;
	while (argv[++i])
	{
		if (!ph_isdigit_str(argv[i]))
		{
			error = "Error: arguments must only contain numbers\n";
			write(2, error, ph_strlen(error));
			return ((1));
		}
	}
	return (0);
}

/*
Validates all command-line arguments for the simulation.
Calls helper functions to check the syntax:
	number of philosophers, times, and meals.
Returns 1 if any argument is invalid, otherwise returns 0.
*/
int	ph_parser(char **argv)
{
	int	check;

	check = ph_check_syntax(argv);
	if (check)
		return (1);
	check = ph_check_philos(argv[1]);
	if (check)
		return (1);
	check = ph_check_times(argv[2], argv[3], argv[4]);
	if (check)
		return (1);
	if (argv[5])
		check = ph_check_meals(argv[5]);
	if (check)
		return (1);
	return (0);
}
