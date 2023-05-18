/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:05:11 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/15 11:02:02 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->start);
	free(data->philo);
	free(data->fork);
}

void	philo_death(t_data *data)
{
	int		i;

	while (!check_finish(data))
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (is_philo_dead(data, i))
			{
				print_action(data, data->philo[i].num, "died");
				pthread_mutex_lock(&(data->check));
				data->died = 1;
				pthread_mutex_unlock(&(data->check));
				break ;
			}
			i++;
		}
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
	pthread_mutex_lock(&(data->start));
	pthread_mutex_unlock(&(data->start));
	if (!(philo->num % 2) && data->n_philo > 1)
		ft_usleep(data->t_eat, data);
	while (!check_finish(data))
	{
		take_fork(philo);
		print_action(data, philo->num, "is sleeping");
		ft_usleep(data->t_sleep, data);
		print_action(data, philo->num, "is thinking");
		if (data->n_philo % 2 != 0)
			ft_usleep(((data->t_death - (data->t_eat \
				+ data->t_sleep)) / 2), data);
	}
	return (NULL);
}

int	launch(t_data *data)
{
	int		i;
	int		ret;

	i = 0;
	if (data->n_philo == 1)
	{
		print_action(data, 1, "has taken a fork");
		ft_usleep(data->t_death, data);
		print_action(data, 1, "died");
		free(data->philo);
		free(data->fork);
		return (0);
	}
	else
	{
		ret = thread_init(data);
		philo_death(data);
		kill_clean(data);
	}
	return (ret);
}
