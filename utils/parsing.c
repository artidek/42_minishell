/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:49:52 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:39:02 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	join_arg(char **arg, char **arr)
{
	int		i;
	char	*temp;

	i = 0;
	free(*arg);
	while (arr[i])
	{
		if (i == 0)
			*arg = ft_strdup(arr[i]);
		temp = ft_strdup(*arg);
		free(*arg);
		*arg = ft_strjoin(temp, arr[i]);
		free(temp);
		i++;
	}
}

void	check_double_quote(char **arg, t_main_dat *main_data)
{
	char	**temp;

	trim_arg(arg);
	temp = ft_split(*arg, '\"');
	if (arr_len(temp) <= 1)
	{
		free_arr(temp);
		return ;
	}
	join_arg(arg, temp);
	expandable(arg, main_data);
}

void	check_single_quote(char **arg, t_main_dat *main_data)
{
	char	**temp;

	trim_arg(arg);
	temp = ft_split(*arg, '\'');
	if (arr_len(temp) <= 1)
	{
		free_arr(temp);
		return ;
	}
	join_arg(arg, temp);
	expandable(arg, main_data);
}
