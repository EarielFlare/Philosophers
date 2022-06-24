/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:20:05 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/23 20:58:48 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->phil_num;
	sem_unlink("forks");
	rules->forks2 = sem_open ("forks", O_CREAT, S_IRWXU, i);
	sem_unlink("writing");
	rules->writing2 = sem_open ("writing", O_CREAT, S_IRWXU, 1);
	sem_unlink("globe_pause");
	rules->globe_pause = sem_open ("globe_pause", O_CREAT, S_IRWXU, 1);
	sem_unlink("death_sem");
	rules->death_sem = sem_open ("death_sem", O_CREAT, S_IRWXU, 0);
	if (rules->forks2 == SEM_FAILED
		|| rules->writing2 == SEM_FAILED
		|| rules->globe_pause == SEM_FAILED
		|| rules->death_sem == SEM_FAILED)
		return (free_sem(rules));
	return (0);
}

int	launcher(t_rules *rules)
{
	rules->phils = (t_phil *)
		malloc(sizeof(t_phil) * rules->phil_num);
	if (rules->phils == NULL)
		return (free_sem(rules));
	rules->launch_time = timestamp(&rules->tv);
	sem_wait(rules->globe_pause);
	if (init_launch_phil(rules, 0))
	{
		free_sem(rules);
		free(rules->phils);
		return (1);
	}
	if (pthread_create((&rules->killer_thread),
			NULL, killer, (void *)rules))
		return (1);
	sem_post(rules->globe_pause);
	return (0);
}

int	init_launch_phil(t_rules *rules, int i)
{
	t_phil	*phil;

	while (i < rules->phil_num)
	{
		phil = &rules->phils[i];
		phil->rules = rules;
		phil->phil_id = i;
		phil->death_note = 0;
		phil->x_ate = 0;
		phil->last_meal = timestamp(&phil->tv);
		phil->deadline = phil->last_meal + rules->life_time;
		phil->thread_id = fork();
		if (phil->thread_id == -1)
			return (error_manager(6));
		else if (phil->thread_id == 0)
			phil_thread(phil);
		i++;
	}
	return (0);
}

void	exit_launcher(t_rules *rules)
{
	int	i;

	i = (int) rules->phil_num;
	while (i--)
		waitpid(-1, NULL, 0);
	sem_post(rules->death_sem);
	pthread_join(rules->killer_thread, NULL);
	free_sem(rules);
	free(rules->phils);
}
