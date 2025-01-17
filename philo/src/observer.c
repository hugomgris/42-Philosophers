/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/17 17:10:55 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ph_check_simulation_end(t_table *table)
{
	bool	check;

	check = false;
	pthread_mutex_lock(&table->stop_lock);
	if (table->stop_flag == true)
		check = true;
	pthread_mutex_unlock(&table->stop_lock);
	return (check);
}
