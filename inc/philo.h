/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:57:12 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/14 15:10:15 by tde-sous         ###   ########.fr       */
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

