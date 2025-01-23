/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:56:52 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/23 11:31:17 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define DIM "\033[2m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define BLINK "\033[5m"

// Cute foreground colors
# define PINK "\033[38;5;200m"
# define LAVENDER "\033[38;5;177m"
# define AQUA "\033[38;5;123m"
# define PEACH "\033[38;5;216m"
# define MINT "\033[38;5;121m"
# define SKY_BLUE "\033[38;5;117m"
# define CREAM "\033[38;5;230m"
# define RED "\033[1;38;5;198m"

//ERROR MSGS
# define MALLOC_ERR "[philo] Error: Memory allocation failed\n"
# define SEM_ERR "[philo] Error: Semaphore creation failed\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				is_dead;
	int				meals_eaten;
	time_t			t_eat;
	time_t			next_meal;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int		n_philos;
	time_t	t_die;
	time_t	t_eat;
	time_t	t_sleep;
	time_t	t_start;
	int		meal_counter;
	int		current_meal;
	int		max_meals;
	bool	stop_flag;
	sem_t	*forks_sem;
	sem_t	*death_sem;
	sem_t	*stop_sem;
	sem_t	*print_sem;
	t_philo	**philos;
}	t_table;

typedef enum e_status
{
	DEAD = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK = 4,
}	t_status;

//PARSING functions
void	ph_arg_error(void);
int		ph_parser(char **argv);
int		ph_check_philos(char *philos);
int		ph_check_times(char *die, char *eat, char *sleep);
int		ph_check_meals(char *meals);

//UTILS functions
int		ph_strlen(const char *s);
int		ph_atoi(const char *str);
int		ph_isdigit_str(const char *str);

//INIT functions
t_table	*ph_init_table(char **argv);
bool	ph_init_sems(t_table *table);
t_philo	**ph_init_philos(t_table *table);

//EXITING functions
void	ph_exit(t_table *table, int code);
void	ph_cleanup_semaphores(t_table *table);
void	ph_cleanup_table(t_table *table);
void	ph_end_processes(t_table *table);
void	ph_error(const char *msg, t_table *table);
void	ph_end_processes(t_table *table);

//TIMER functions
time_t	ph_get_time(void);
void	ph_delay(time_t t_start);

//PRINTER functions
void	ph_process_status(t_philo *philo, t_status status);
void	ph_print_status(t_philo *philo, char *status);

//SIMULATION functions
bool	ph_start(t_table *table);
void	ph_routine(t_philo *philo);
void	ph_take_fork(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	ph_eat(t_philo *philo);

//OBSERVER functions
void	*ph_observe(void *arg);
void	ph_monitor_processes(t_table *table);

#endif
