/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:22:59 by abiddane          #+#    #+#             */
/*   Updated: 2023/03/17 11:08:34 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(char *nptr)
{
	int					i;
	int					comp;
	long long int		n;

	i = 0;
	comp = 1;
	n = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			comp *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + nptr[i] - '0';
		i++;
	}
	return (n * comp);
}

long long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&(data->print));
	printf("%lld ", ft_time() - data->z_time);
	printf("%d ", id);
	printf("%s\n", str);
	pthread_mutex_unlock(&(data->print));
}

void	ft_usleep(int time, t_data *data)
{
	long long	present;

	present = ft_time();
	while (!check_death_eat(data))
	{
		if (ft_time() - present >= time)
			break ;
		usleep(time);
	}
}
