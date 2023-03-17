/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:18:14 by abiddane          #+#    #+#             */
/*   Updated: 2023/03/03 13:17:16 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_arg(int ac, char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) > 2147483647)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '+')
				j++;
			while (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			if (av[i][j] != '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	send_error(char *msg)
{
	int	i;

	i = ft_strlen(msg);
	write(2, "Error\n", 6);
	write(2, msg, i);
	write(2, "\n", 1);
	return (1);
}

int	handle_error(int i)
{
	if (i == 1)
		send_error("Invalid arguments");
	if (i == 2)
		send_error("Failed mutex init");
	return (1);
	if (i == 3)
		send_error("Failed thread init");
	if (i == 4)
		send_error("Failed philo allocation");
}
