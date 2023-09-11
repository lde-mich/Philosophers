/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:56:34 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/18 16:06:14 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_check_death(void *vd_philo)
{
	t_philo	*philo;

	philo = (t_philo *)vd_philo;
	while (42)
	{
		if ((ft_mstime() - philo->temph) >= philo->data->tmp_die
			&& philo->n_eat != 0)
		{
			printf("%d %d  died\n", ft_mstime() - philo->data->t,
				philo->id);
			philo->data->dead = 0;
			break ;
		}
		philo = philo->next;
	}
	return (0);
}

void	ft_print(t_philo *philo, char *action)
{
	usleep(100);
	if (!philo->data->dead)
		return ;
	printf("%d %d %s\n", ft_mstime() - philo->data->t, philo->id, action);
}

int	ft_mstime(void)
{
	struct timeval	tv_u;

	gettimeofday(&tv_u, 0);
	return ((tv_u.tv_sec * 1000) + (tv_u.tv_usec / 1000));
}

void	ft_msleep(int t)
{
	int	tstart;

	tstart = ft_mstime();
	while (ft_mstime() - tstart < t)
		usleep(150);
}

void	ft_free_all(t_philo	*philo)
{
	int			i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		philo = philo->next;
		i++;
	}
}
