/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:40:55 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/15 11:01:57 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_eat(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->check));
	while (i < data->n_philo && data->philo[i].eat >= data->n_eat
		&& data->n_eat != -1)
		i++;
	if (i == data->n_philo)
		data->all_eat = 1;
	pthread_mutex_unlock(&(data->check));
}

int	is_philo_dead(t_data *data, int i)
{
	pthread_mutex_lock(&(data->time));
	if (ft_time() - data->philo[i].last_eat >= data->t_death)
	{
		pthread_mutex_unlock(&(data->time));
		return (1);
	}
	pthread_mutex_unlock(&(data->time));
	return (0);
}

int	check_finish(t_data *data)
{
	pthread_mutex_lock(&(data->check));
	if (data->died == 0 && (data->all_eat == -1 || data->all_eat == 0))
	{
		pthread_mutex_unlock(&(data->check));
		return (0);
	}
	pthread_mutex_unlock(&(data->check));
	return (1);
}
