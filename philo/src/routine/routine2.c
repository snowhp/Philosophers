/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:55:24 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/19 13:34:41 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philostats *philo, char *str)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->isdprint == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->print);
	ft_printf("%i %i", ft_gettime() - philo->data->startime, (*philo).id + 1);
	ft_printf(" %s\n", str);
	pthread_mutex_unlock(&philo->data->print);
}

int	ft_gettime(void)
{
	struct timeval	currenttime;

	if (gettimeofday(&currenttime, NULL) != 0)
		return (ft_printf("Error getting time"), 0);
	return ((currenttime.tv_sec * 1000) + (currenttime.tv_usec / 1000));
}
