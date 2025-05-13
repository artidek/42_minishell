/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:02:56 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/13 19:49:39 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isalldigit(char *str)
{
	if (str && *str)
	{
		while (*str)
		{
			if (!ft_isdigit((int)*str))
				return (0);
			str++;
		}
	}
	else
		return (0);
	return (1);
}
