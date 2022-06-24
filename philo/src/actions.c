/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:14:16 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/22 21:26:00 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phil_thread_prepare(t_phil *phil)
{
	t_rules			*rules;

	rules = phil->rules;
	pthread_mutex_lock(&rules->globe_var);
	pthread_mutex_unlock(&rules->globe_var);
	phil->last_meal = timestamp(&phil->tv);
	pthread_mutex_lock(phil->status);
	phil->deadline = phil->last_meal + rules->life_time;
	pthread_mutex_unlock(phil->status);
}

void	*phil_thread(void *void_phil)
{
	t_phil			*phil;
	t_rules			*rules;

	phil = (t_phil *)void_phil;
	rules = phil->rules;
	phil_thread_prepare(phil);
	if (phil->phil_id % 2)
		usleep(rules->create_delay + 10000);
	pthread_mutex_lock(&rules->globe_var);
	while (!rules->death_note)
	{
		pthread_mutex_unlock(&rules->globe_var);
		if (!philo_eats(phil))
			return (NULL);
		action_print(rules, phil->phil_id, "is sleeping");
		smart_sleep(rules->sleep_time, phil);
		action_print(rules, phil->phil_id, "is thinking");
		pthread_mutex_lock(&rules->globe_var);
	}
	pthread_mutex_unlock(&rules->globe_var);
	return (NULL);
}
