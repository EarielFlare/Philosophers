/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:20:05 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/23 09:03:48 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->phil_num;
	rules->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * i);
	if (rules->forks == NULL)
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&rules->writing, NULL))
		return (1);
	if (pthread_mutex_init(&rules->globe_var, NULL))
		return (1);
	return (0);
}

int	init_mutex2(t_rules *rules)
{
	int	i;

	i = rules->phil_num;
	rules->status = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * i);
	if (rules->status == NULL)
	{
		free(rules->forks);
		return (1);
	}
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->status[i]), NULL))
			return (1);
	}
	return (0);
}

int	launcher(t_rules *rules)
{
	rules->phils = (t_phil *)
		malloc(sizeof(t_phil) * rules->phil_num);
	if (rules->phils == NULL)
	{
		free(rules->forks);
		free(rules->status);
		return (1);
	}
	rules->launch_time = timestamp(&rules->tv);
	pthread_mutex_lock(&rules->globe_var);
	if (init_launch_phil(rules, 0))
		return (1);
	if (init_launch_phil(rules, 1))
		return (1);
	rules->create_time = timestamp(&rules->tv);
	rules->create_delay = rules->create_time - rules->launch_time;
	pthread_mutex_unlock(&rules->globe_var);
	if (pthread_create(&(rules->monitor_thread),
			NULL, monitor, (void *)rules))
		return (1);
	exit_launcher(rules);
	return (0);
}

void	exit_launcher(t_rules *rules)
{
	int	i;

	pthread_join(rules->monitor_thread, NULL);
	i = -1;
	while (++i < rules->phil_num)
		pthread_join(rules->phils[i].thread_id, NULL);
	i = -1;
	while (++i < rules->phil_num)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->status[i]);
	}
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->globe_var);
	free(rules->phils);
	free(rules->status);
	free(rules->forks);
}

int	init_launch_phil(t_rules *rules, int i)
{
	t_phil	*phil;

	while (i < rules->phil_num)
	{
		phil = &rules->phils[i];
		phil->rules = rules;
		phil->phil_id = i;
		phil->x_ate = 0;
		phil->right_fork = &rules->forks[i];
		phil->left_fork = &rules->forks[(i + 1) % rules->phil_num];
		phil->status = &rules->status[i];
		phil->last_meal = timestamp(&phil->tv);
		phil->deadline = phil->last_meal + rules->life_time;
		if (pthread_create(&rules->phils[i].thread_id,
				NULL, phil_thread, (void *)&rules->phils[i]))
			return (1);
		i += 2;
	}
	return (0);
}
