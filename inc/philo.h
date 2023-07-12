/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:57:12 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/12 20:10:49 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philostats
{
	int	lastmeal;
	int	id;

}	t_philostats;

typedef struct s_philos
{
	pthread_t	*id;
	t_philostats *philo;
	int	nphilo;
	int	tdie;
	int	teat;
	int	tsleep;
	int	tmusteat;
}	t_philos;
