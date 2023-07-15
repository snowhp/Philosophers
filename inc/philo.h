/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:57:12 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/15 10:16:55 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philos
{
	pthread_t	*id;
	int	nphilo;
	int	tdie;
	int	teat;
	int	tsleep;
	int	tmusteat;
	int	isdead;
	int	startime;
	pthread_mutex_t print;
	pthread_mutex_t *forks;
}	t_philos;

typedef struct s_philostats
{
	int	lastmeal;
	int	id;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	t_philos	*data;
}	t_philostats;

void	ft_startphilo(t_philostats *philo, t_philos *s);
void	ft_initstruct(t_philos *s);
void	ft_initmutex(t_philos *s);
void	ft_destroymutex(t_philos *s);
void	ft_freeall(t_philostats *philo, t_philos *s);
void	ft_print(t_philostats *philo, char *str);
int	ft_gettime();
int	ft_checklastmeal(t_philostats *philo);
