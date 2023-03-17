/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:05:11 by abiddane          #+#    #+#             */
/*   Updated: 2023/03/17 11:19:44 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (check_death_eat(data))
		return (1);
	if (eat_util(philo))
		return (1);
	eat_time(philo);
	print_action(data, philo->num, "is eating");
	ft_usleep(data->t_eat, data);
	pthread_mutex_lock(&(data->check));
	philo->eat += 1;
	pthread_mutex_unlock(&(data->check));
	pthread_mutex_unlock(&(data->fork[philo->fork_l]));
	pthread_mutex_unlock(&(data->fork[philo->fork_r]));
	return (0);
}

void	kill_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philo[i].thd, NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->check);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
	free(data->philo);
	free(data->fork);
}

void	philo_death(t_data *data)
{
	int		i;

	while (!check_death_eat(data))
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&(data->death));
			if (dead_time(data, i))
			{
				print_action(data, data->philo[i].num, "died");
				data->died = 1;
				pthread_mutex_unlock(&(data->death));
				break ;
			}
			pthread_mutex_unlock(&(data->death));
			i++;
		}
		if (check_death_eat(data))
			break ;
		check_all_eat(data);
	}
	return ;
}

void	*rout(void *philoche)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philoche;
	data = philo->data;
	if (!(philo->num % 2) && data->n_philo > 1)
		usleep(data->t_eat * 1000);
	while (!check_death_eat(data))
	{
		if (check_death_eat(data))
			break ;
		if (philo_eating(philo))
			break ;
		if (check_death_eat(data))
			break ;
		print_action(data, philo->num, "is sleeping");
		ft_usleep(data->t_sleep, data);
		if (check_death_eat(data))
			break ;
		print_action(data, philo->num, "is thinking");
	}
	return (NULL);
}

int	launch(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->n_philo)
	{
		philo = &(data->philo[i]);
		if (pthread_create(&(philo->thd), NULL, rout, philo))
		{
			i--;
			while (i-- >= 0)
			{
				pthread_join(philo->thd, NULL);
			}
			free(data->philo);
			free(data->fork);
			return (3);
		}
		eat_time(philo);
		i++;
	}
	philo_death(data);
	kill_clean(data);
	return (0);
}
