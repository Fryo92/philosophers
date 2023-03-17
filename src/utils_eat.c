/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:45:56 by abiddane          #+#    #+#             */
/*   Updated: 2023/03/03 15:25:34 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	last_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->fork[philo->fork_r]));
	print_action(data, philo->num, "has taken a fork");
	if (check_death_eat(data) == 1 || data->n_philo == 1)
	{
		pthread_mutex_unlock(&(data->fork[philo->fork_r]));
		return (1);
	}
	pthread_mutex_lock(&(data->fork[philo->fork_l]));
	if (check_death_eat(data) == 1)
	{
		pthread_mutex_unlock(&(data->fork[philo->fork_r]));
		pthread_mutex_unlock(&(data->fork[philo->fork_l]));
		return (1);
	}
	print_action(data, philo->num, "has taken a fork");
	return (0);
}

int	take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->fork[philo->fork_l]));
	if (check_death_eat(data) == 1)
	{
		pthread_mutex_unlock(&(data->fork[philo->fork_l]));
		return (1);
	}
	print_action(data, philo->num, "has taken a fork");
	pthread_mutex_lock(&(data->fork[philo->fork_r]));
	if (check_death_eat(data) == 1)
	{
		pthread_mutex_unlock(&(data->fork[philo->fork_l]));
		pthread_mutex_unlock(&(data->fork[philo->fork_r]));
		return (1);
	}
	print_action(data, philo->num, "has taken a fork");
	return (0);
}

int	eat_util(t_philo *philo)
{
	t_data	*data;
	int		ret;

	data = philo->data;
	if (philo->num == data->n_philo)
	{
		if (last_fork(philo))
			return (1);
	}
	else
	{
		if (take_fork(philo))
			return (1);
	}
	return (0);
}
