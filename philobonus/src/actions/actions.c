/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:56 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/17 15:28:39 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philoeat(t_philostats *philo)
{
	if (!ft_checklastmeal(philo) || philo->data->isdead == 1)
		return (NULL);
	sem_wait(philo->data->forks);
	ft_print(philo, "has taken a fork");
	if (!ft_checklastmeal(philo) || philo->data->isdead == 1)
		return (NULL);
	if (philo->data->nphilo == 1)
		usleep(philo->data->tdie * 1000);
	else
	{
		sem_wait(philo->data->forks);
		ft_print(philo, "has taken a fork");
	}
	if (!ft_checklastmeal(philo) || philo->data->isdead == 1)
		return (NULL);
	ft_print(philo, "is eating");
	philo->lastmeal = ft_gettime();
	usleep(philo->data->teat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (NULL);
}

void	*ft_philosleep(t_philostats *philo)
{
	if (!ft_checklastmeal(philo) || philo->data->isdead == 1)
		return (NULL);
	ft_print(philo, "is sleeping");
	usleep(philo->data->tsleep * 1000);
	if (!ft_checklastmeal(philo) || philo->data->isdead == 1)
		return (NULL);
	if (philo->data->isdead != 1)
		ft_print(philo, "is thinking");
	if (!ft_checklastmeal(philo) || philo->data->isdead == 1)
		return (NULL);
	return (NULL);
}
