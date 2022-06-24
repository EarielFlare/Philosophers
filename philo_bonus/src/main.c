/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:11:45 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/22 16:33:54 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parser(t_rules *rules, char **argv)
{
	ft_atoi_char(argv[1], &(rules->phil_num));
	ft_atoi_char(argv[2], &(rules->life_time));
	ft_atoi_char(argv[3], &(rules->eat_time));
	ft_atoi_char(argv[4], &(rules->sleep_time));
	if (rules->phil_num < 1 || rules->life_time < 0
		|| rules->eat_time < 0 || rules->sleep_time < 0
		|| rules->phil_num > 250)
		return (3);
	if (argv[5])
	{
		ft_atoi_char(argv[5], &(rules->eat_count));
		if (rules->eat_count <= 0)
			return (3);
	}
	else
		rules->eat_count = -1;
	return (0);
}

void	*killer(void *void_rules)
{
	t_rules			*rules;
	int				i;

	rules = (t_rules *)void_rules;
	sem_wait(rules->death_sem);
	i = -1;
	while (++i < rules->phil_num)
		kill(rules->phils[i].thread_id, SIGKILL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (error_manager(1));
	if (args_not_valid(argc, argv))
		return (error_manager(2));
	if (parser(&rules, argv))
		return (error_manager(3));
	if (init_mutex(&rules))
		return (error_manager(4));
	if (launcher(&rules))
		return (error_manager(5));
	exit_launcher(&rules);
	return (0);
}
