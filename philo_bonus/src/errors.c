/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:49:47 by cgregory          #+#    #+#             */
/*   Updated: 2022/06/22 16:13:51 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
}

int	error_manager(int error)
{
	if (error == 1)
		write_error("Wrong amount of arguments");
	if (error == 2)
		write_error("The arguments must be numbers");
	if (error == 3)
		write_error("At least one wrong argument found");
	if (error == 4)
		write_error("Fatal error when intializing semaphores");
	if (error == 5)
		write_error("Fatal error when creating processes");
	if (error == 6)
		write_error("Fork error");
	return (1);
}

int	args_not_valid(int argc, char **argv)
{
	char	*str;

	while (--argc)
	{
		str = argv[argc];
		while (*str)
		{
			if (*str < 48 || *str > 57)
				return (1);
			str++;
		}		
	}
	return (0);
}
