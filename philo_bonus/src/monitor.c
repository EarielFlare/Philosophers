/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:30:35 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/24 07:37:34 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_death_note(t_phil *phil)
{
//	pthread_mutex_lock(&phil->death_mutex);
	sem_wait(phil->death_mutex);
	phil->death_note = 1;
//	pthread_mutex_unlock(&phil->death_mutex);
	sem_post(phil->death_mutex);
}

void	*monitor(void *void_phil)
{
	t_phil			*phil;

	phil = (t_phil *)void_phil;
//	pthread_mutex_lock(&phil->death_mutex);
	sem_wait(phil->death_mutex);
	while (!phil->death_note)
	{
//		pthread_mutex_unlock(&phil->death_mutex);
		sem_post(phil->death_mutex);
		phil->curr_time = timestamp(&phil->tv);
//		pthread_mutex_lock(&phil->dline_mutex);
		sem_wait(phil->dline_mutex);
		if (phil->curr_time > phil->deadline)
		{
			action_print(phil, phil->phil_id, "died");
			set_death_note(phil);
			sem_post(phil->rules->death_sem);
			sem_wait(phil->rules->writing2);
		}
		else if (phil->rules->eat_count != -1
			&& phil->x_ate >= phil->rules->eat_count)
			set_death_note(phil);
//		pthread_mutex_unlock(&phil->dline_mutex);
		sem_post(phil->dline_mutex);
		usleep(200);
//		pthread_mutex_lock(&phil->death_mutex);
		sem_wait(phil->death_mutex);
	}
//	pthread_mutex_unlock(&phil->death_mutex);
	sem_post(phil->death_mutex);
	return (NULL);
}
