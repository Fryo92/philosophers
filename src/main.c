/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:38:07 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/15 10:55:04 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		ret;

	if (ac != 5 && ac != 6)
		return (send_error("Wrong number of arguments"));
	if (check_arg(av))
		return (send_error("Invalid arguments"));
	ret = init_data(&data, av);
	if (ret)
		return (handle_error(ret));
	ret = launch(&data);
	if (ret)
		return (handle_error(ret));
	return (0);
}
