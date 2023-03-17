/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:07:03 by abiddane          #+#    #+#             */
/*   Updated: 2023/03/03 14:07:41 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		return (2);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (2);
		i++;
	}
	if (pthread_mutex_init(&(data->print), NULL))
		return (2);
	if (pthread_mutex_init(&(data->death), NULL))
		return (2);
	if (pthread_mutex_init(&(data->check), NULL))
		return (2);
	if (pthread_mutex_init(&(data->time), NULL))
		return (2);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
	{
		free(data->fork);
		return (1);
	}
	while (i < data->n_philo)
	{
		data->philo[i].num = i + 1;
		data->philo[i].eat = 0;
		data->philo[i].fork_l = i;
		data->philo[i].fork_r = (i + 1) % data->n_philo;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_death = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->n_eat = ft_atoi(av[5]);
		if (data->n_eat <= 0)
			return (1);
	}
	else
		data->n_eat = -1;
	data->all_eat = 0;
	data->died = 0;
	data->z_time = ft_time();
	if (init_mutex(data))
	{
		free(data->fork);
		return (2);
	}
	if (init_philo(data))
		return (4);
	return (0);
}
