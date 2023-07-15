/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:55:24 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/15 10:16:48 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philostats *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	ft_printf("%i %i", ft_gettime() - philo->data->startime, (*philo).id + 1);
	ft_printf(" %s\n", str);
	pthread_mutex_unlock(&philo->data->print);
}
int	ft_gettime()
{
	struct timeval currentTime;

	if (gettimeofday(&currentTime, NULL) != 0)
		return (ft_printf("Error getting time"), 0);
	return (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
}

/* Check for last meal*/
int	ft_checklastmeal(t_philostats *philo)
{
	if (ft_gettime() - philo->lastmeal >= philo->data->tdie)
	{
		philo->data->isdead = 1;
		ft_print(philo, "died");
		return 0;
	}
	return 1;
}
