/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:09:53 by cgregory          #+#    #+#             */
/*   Updated: 2022/05/22 13:41:46 by cgregory         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

char	ft_atoi_char(const char *str, long *nmbr)
{
	int	sign;

	sign = 1;
	*nmbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -sign;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		*nmbr = *nmbr * 10 + (*str - '0');
		str++;
	}
	*nmbr = *nmbr * sign;
	if (*nmbr > 2147483647)
		return ('H');
	else if (*nmbr < -2147483648)
		return ('L');
	else
		return ('K');
}
