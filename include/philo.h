/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:41:14 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/15 11:03:16 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int				num;
	int				eat;
	int				fork_l;
	int				fork_r;
	long long		last_eat;
	struct s_data	*data;
	pthread_t		thd;
}				t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				all_eat;
	long long		z_time;
	int				died;
	pthread_mutex_t	time;
	pthread_mutex_t	check;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	start;
	t_philo			*philo;
}				t_data;

/* init.c */
int			init_data(t_data *data, char **av);
int			thread_init(t_data *data);

/* error.c */
int			check_arg(char **av);
int			send_error(char *msg);
int			handle_error(int i);

/* routine.c */
int			thread_init(t_data *data);
int			launch(t_data *data);
void		*rout(void *philoche);

/* utils_check */
void		check_all_eat(t_data *data);
void		last_eat_time(t_philo *philo);
int			is_philo_dead(t_data *data, int i);
int			check_finish(t_data *data);

/* utils_eat.c */
void		take_fork(t_philo *philo);

/* utils.c */
long long	ft_atoi(char *nptr);
long long	ft_time(void);
void		print_action(t_data *data, int id, char *str);
void		ft_usleep(int time, t_data *data);

#endif