/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:24:30 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/15 10:20:00 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isformatted(char **argv, int argc, t_philos *s)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	while (argv[i])
	{
		if (!ft_isnum(argv[i++]))
			return (ft_printf("%s not a valid number\n", argv[i - 1]), 0);
	}
	s->nphilo = ft_atoi(argv[1]);
	if (s->nphilo <= 0)
		return (ft_printf("Not enough philosophers\n"), 0);
	s->tdie = ft_atoi(argv[2]);
	if (s->tdie <= 0)
		return (ft_printf("Wrong time to die\n"), 0);
	s->teat = ft_atoi(argv[3]);
	if (s->teat <= 0)
		return (ft_printf("Wrong time to eat\n"), 0);
	s->tsleep = ft_atoi(argv[4]);
	if (s->tsleep <= 0)
		return (ft_printf("Wrong time to sleep\n"), 0);
	if (argv[5])
	{
		s->tmusteat = ft_atoi(argv[5]);
		if (s->tmusteat <= 0)
			return (ft_printf("Wrong time to each philo eats\n"), 0);
	}
	return (1);
}

void	*ft_philoeat(t_philostats *philo)
{
	/* Take Left Fork*/
	if (!ft_checklastmeal(philo))
		return NULL;
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, "has taken a fork");

	if (!ft_checklastmeal(philo))
			return NULL;
	/* Take Right Fork*/
	if (philo->data->nphilo == 1)
		usleep(philo->data->tdie * 1000);
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "has taken a fork");
	}

	/*Check last meal*/
	if (!ft_checklastmeal(philo))
		return NULL;
	ft_print(philo, "is eating");
	philo->lastmeal = ft_gettime();//Save the last meal
	usleep(philo->data->teat * 1000);//Eat in useconds

	/* Unlock forks */
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return NULL;
}

void	*ft_philosleep(t_philostats *philo)
{
	if (!ft_checklastmeal(philo))
		return NULL;
	ft_print(philo, "is sleeping");
	usleep(philo->data->tsleep * 1000);

	if (!ft_checklastmeal(philo))
		return NULL;
	if (philo->data->isdead != 1)
		ft_print(philo, "is thinking");
	if (!ft_checklastmeal(philo))
		return NULL;
	return NULL;
}

void	*ft_runphilos(void *arg)
{
	t_philostats philo;
	int	eat;

	eat = 0;
	philo = *(t_philostats*)arg;
	philo.lastmeal = ft_gettime();//Save join time
	while (!philo.data->isdead)
	{
		if (philo.data->isdead == 1)
			break;
		ft_philoeat(&philo);
		eat++;
		if (eat == philo.data->tmusteat || philo.data->isdead == 1)
			break ;
		ft_philosleep(&philo);
	}
	if (pthread_mutex_lock(&philo.data->print) != 0)
		return (ft_printf("Failed to lock a mutex"), NULL);
	//ft_printf("Hello i am philo %i\n", philo.id + 1);
	if (pthread_mutex_unlock(&philo.data->print) != 0)
		return (ft_printf("Failed to unlock a mutex"), NULL);
	return (0);
}


int	ft_startphilos(t_philos *s)
{
	int	i;
	t_philostats	*philo;

	philo = (t_philostats *)malloc(s->nphilo * sizeof(t_philostats));
	s->id = (pthread_t *)malloc(s->nphilo * sizeof(pthread_t));
	s->forks = (pthread_mutex_t *)malloc(s->nphilo * sizeof(pthread_mutex_t));
	ft_startphilo(philo, s);
	i = 0;
	ft_initmutex(s);
	s->startime = ft_gettime();
	while (i < s->nphilo)
	{
		if (i % 2 == 0)
			pthread_create(&s->id[i], NULL, &ft_runphilos, &philo[i]);
		i++;
		usleep(1000);//Time to let the philo's seat at the table
	}
	i = 0;
	while (i < s->nphilo)
	{
		if (i % 2 != 0)
			pthread_create(&s->id[i], NULL, &ft_runphilos, &philo[i]);
		i++;
		usleep(1000);//Time to let the philo's seat at the table
	}
	i = 0;
	while (i < s->nphilo)
	{
		if (pthread_join(s->id[i], NULL) != 0)
			return (ft_printf("Failed to join thread"), 0);
		i++;
	}
	//ft_freeall(philo, s);
	ft_destroymutex(s);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philos	s;

	ft_initstruct(&s);
	if (!ft_isformatted(argv, argc, &s))
		return (1);
	if (!ft_startphilos(&s))
		return (1);
	return (0);
}
