/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:14:16 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/24 07:39:57 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	phil_thread_prepare(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
//	pthread_mutex_init(&phil->death_mutex, NULL);
//	pthread_mutex_init(&phil->dline_mutex, NULL);
	sem_unlink("death_mutex");
	phil->death_mutex = sem_open ("death_mutex", O_CREAT, S_IRWXU, 1);
	sem_unlink("dline_mutex");
	phil->dline_mutex = sem_open ("dline_mutex", O_CREAT, S_IRWXU, 1);
	pthread_create(&phil->monitor_thread,
		NULL, monitor, (void *)phil);
	sem_wait(rules->globe_pause);
	sem_post(rules->globe_pause);
	phil->last_meal = timestamp(&phil->tv);
//	pthread_mutex_lock(&phil->dline_mutex);
	sem_wait(phil->dline_mutex);
	phil->deadline = phil->last_meal + rules->life_time;
//	pthread_mutex_unlock(&phil->dline_mutex);
	sem_post(phil->dline_mutex);
}

void	phil_thread_destroy(t_phil *phil)
{
	t_rules	*rules;

	rules = phil->rules;
//	pthread_mutex_destroy(&phil->death_mutex);
//	pthread_mutex_destroy(&phil->dline_mutex);
	sem_close(phil->death_mutex);
	sem_unlink("death_mutex");
	sem_close(phil->dline_mutex);
	sem_unlink("dline_mutex");
	free_sem(rules);
	free(rules->phils);
}

int	phil_thread(t_phil *phil)
{
	phil_thread_prepare(phil);
	if (phil->phil_id % 2)
		usleep(20000);
//	pthread_mutex_lock(&phil->death_mutex);
	sem_wait(phil->death_mutex);
	while (!phil->death_note)
	{
//		pthread_mutex_unlock(&phil->death_mutex);
		sem_post(phil->death_mutex);
		philo_eats(phil);
		action_print(phil, phil->phil_id, "is sleeping");
		smart_sleep(phil->rules->sleep_time, phil);
		action_print(phil, phil->phil_id, "is thinking");
//		pthread_mutex_lock(&phil->death_mutex);
		sem_wait(phil->death_mutex);
	}
//	pthread_mutex_unlock(&phil->death_mutex);
	sem_post(phil->death_mutex);
	pthread_join(phil->monitor_thread, NULL);
	phil_thread_destroy(phil);
	exit(0);
}
