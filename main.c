/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:24:30 by tde-sous          #+#    #+#             */
/*   Updated: 2023/07/11 16:39:37 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft/libft.h"

int	main(char **argv, int argc)
{
	ft_isformatted(argv);
	return (0);
}

void	ft_isformatted(char **argv)
{
	int	nphilo;
	int	tdie;
	int	teat;
	int	tsleep;
	int	tmusteat;


	nphilo = ft_atoi(argv[1]);
	tdie = ft_atoi(argv[2]);
	teat = ft_atoi(argv[3]);
	tsleep = ft_atoi(argv[4]);
	if (argv[6])
		tmusteat = ft_atoi(argv[6]);
}
