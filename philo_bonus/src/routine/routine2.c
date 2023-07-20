/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:55:24 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/20 13:19:52 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philostats *philo, char *str)
{
	sem_wait(philo->data->death);
	if (philo->data->isdprint == 1)
	{
		sem_post(philo->data->death);
		return ;
	}
	sem_post(philo->data->death);
	sem_wait(philo->data->print);
	ft_printf("%i %i", ft_gettime() - philo->data->startime, (*philo).id + 1);
	ft_printf(" %s\n", str);
	sem_post(philo->data->print);
}

int	ft_gettime(void)
{
	struct timeval	currenttime;

	if (gettimeofday(&currenttime, NULL) != 0)
		return (ft_printf("Error getting time"), 0);
	return ((currenttime.tv_sec * 1000) + (currenttime.tv_usec / 1000));
}

void	ft_setlastmeal(t_philostats *philo)
{
	sem_wait(philo->meal);
	philo->lastmeal = ft_gettime();
	sem_post(philo->meal);
}
