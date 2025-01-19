/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:12:29 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/17 12:12:33 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
