/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:50:42 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/24 07:34:40 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	timestamp(struct timeval *tv)
{
	unsigned long	curr_time;

	gettimeofday(tv, 0);
	curr_time = tv->tv_sec * 1000 + tv->tv_usec / 1000;
	return (curr_time);
}

void	smart_sleep(unsigned long time, t_phil *phil)
{
	unsigned long	past;
	unsigned long	delta;
	unsigned long	remain;

	past = timestamp(&phil->tv);
	while (1)
	{
		delta = timestamp(&phil->tv) - past;
		if (delta > time)
			break ;
		remain = time - delta;
		if (remain > 1)
			usleep(remain * 900);
		else
			usleep(50);
	}
}

void	action_print(t_phil *phil, int id, char *string)
{
	unsigned long	curr_time;
	struct timeval	tv;
	t_rules			*rules;

	rules = phil->rules;
//	pthread_mutex_lock(&phil->death_mutex);
	sem_wait(phil->death_mutex);
	if (!phil->death_note)
	{
		curr_time = timestamp(&tv);
		sem_wait(rules->writing2);
		printf("%lu %i %s\n",
			curr_time - rules->launch_time, id + 1, string);
		sem_post(rules->writing2);
	}
//	pthread_mutex_unlock(&phil->death_mutex);
	sem_post(phil->death_mutex);
	return ;
}

int	free_sem(t_rules *rules)
{
	sem_close(rules->forks2);
	sem_close(rules->writing2);
	sem_close(rules->globe_pause);
	sem_close(rules->death_sem);
	sem_unlink("forks");
	sem_unlink("writing");
	sem_unlink("globe_pause");
	sem_unlink("death_sem");
	return (1);
}
