/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:50:42 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/22 16:11:39 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	action_print(t_rules *rules, int id, char *string)
{
	unsigned long	curr_time;

	pthread_mutex_lock(&rules->globe_var);
	if (!rules->death_note)
	{
		curr_time = timestamp(&rules->tv);
		pthread_mutex_lock(&rules->writing);
		printf("%lu %i %s\n",
			curr_time - rules->launch_time, id + 1, string);
		pthread_mutex_unlock(&rules->writing);
	}
	pthread_mutex_unlock(&rules->globe_var);
	return ;
}
