/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaidaou <nbaidaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:14:58 by nbaidaou          #+#    #+#             */
/*   Updated: 2025/02/06 16:15:25 by nbaidaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Seed for the random number generator
static unsigned long	seed = 1;

// Custom rand() function
int	ft_rand(void)
{
	unsigned long	a;
	unsigned long	c;

	// Constants for the LCG (same as used in many standard libraries)
	a = 1103515245;
	c = 12345;
	unsigned long m = 2147483648; // 2^31
	// Update the seed using the LCG formula
	seed = (a * seed + c) % m;
	// Return the random number as an integer
	return (int)(seed % (INT_MAX + 1UL));
}

// Custom srand() function to set the seed
void	ft_srand(unsigned int new_seed)
{
	seed = new_seed;
}