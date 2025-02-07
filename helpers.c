/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:14:58 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/07 16:57:32 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static unsigned long	seed = 1;

int	ft_rand(void)
{
	unsigned long	a;
	unsigned long	c;

	a = 1103515245;
	c = 12345;
	unsigned long m = 2147483648; // 2^31
	seed = (a * seed + c) % m;
	return (int)(seed % (INT_MAX + 1UL));
}

void	ft_srand(unsigned int new_seed)
{
	seed = new_seed;
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	close_handler(t_data *vars)
{
	ft_putstr_fd("Window closed via close button.\n", 1);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}
