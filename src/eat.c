/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:45:56 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/15 11:03:01 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	last_eat_time(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->time));
	philo->last_eat = ft_time();
	pthread_mutex_unlock(&(data->time));
}

void	take_utils(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_action(data, philo->num, "is eating");
	pthread_mutex_lock(&(data->check));
	philo->eat += 1;
	pthread_mutex_unlock(&(data->check));
	last_eat_time(philo);
	ft_usleep(data->t_eat, data);
}

void	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&(data->fork[philo->fork_l]));
		print_action(data, philo->num, "has taken a fork");
		pthread_mutex_lock(&(data->fork[philo->fork_r]));
		print_action(data, philo->num, "has taken a fork");
		take_utils(philo);
		pthread_mutex_unlock(&(data->fork[philo->fork_r]));
		pthread_mutex_unlock(&(data->fork[philo->fork_l]));
	}
	else
	{
		pthread_mutex_lock(&(data->fork[philo->fork_r]));
		print_action(data, philo->num, "has taken a fork");
		pthread_mutex_lock(&(data->fork[philo->fork_l]));
		print_action(data, philo->num, "has taken a fork");
		take_utils(philo);
		pthread_mutex_unlock(&(data->fork[philo->fork_l]));
		pthread_mutex_unlock(&(data->fork[philo->fork_r]));
	}
}
