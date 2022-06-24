/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:30:35 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/22 15:57:06 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_death_note(t_rules *rules)
{
	pthread_mutex_lock(&rules->globe_var);
	rules->death_note = 1;
	pthread_mutex_unlock(&rules->globe_var);
}

void	phils_check_cycle(t_rules *rules, int i)
{
	rules->all_ate = 0;
	while (i < rules->phil_num)
	{
		rules->curr_time = timestamp(&rules->tv);
		pthread_mutex_lock(rules->phils[i].status);
		if (rules->curr_time > rules->phils[i].deadline)
		{
			pthread_mutex_unlock(rules->phils[i].status);
			action_print(rules, rules->phils[i].phil_id, "died");
			set_death_note(rules);
			break ;
		}
		if (rules->eat_count != -1
			&& rules->phils[i].x_ate >= rules->eat_count)
			(rules->all_ate)++;
		if (rules->all_ate == rules->phil_num)
			set_death_note(rules);
		pthread_mutex_unlock(rules->phils[i].status);
		usleep(50);
		i++;
	}
}

void	*monitor(void *void_rules)
{
	t_rules	*rules;

	rules = (t_rules *)void_rules;
	pthread_mutex_lock(&rules->globe_var);
	while (!rules->death_note)
	{
		pthread_mutex_unlock(&rules->globe_var);
		phils_check_cycle(rules, 0);
		pthread_mutex_lock(&rules->globe_var);
	}
	pthread_mutex_unlock(&rules->globe_var);
	return (NULL);
}
