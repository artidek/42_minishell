/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:02:56 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/17 18:04:03 by aobshatk         ###   ########.fr       */
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

int	comp_arr(char **arr1, char **arr2)
{
	int	arrlen1;
	int	arrlen2;
	int	i;

	arrlen1 = arr_len(arr1);
	arrlen2 = arr_len(arr2);
	i = 0;
	if (arrlen1 - 1 == arrlen2 && arrlen2 != 0)
	{
		while (i < arrlen1 - 1)
		{
			if (ft_strncmp(arr1[i], arr2[i], ft_strlen(arr1[i])))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
