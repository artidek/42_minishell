/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:02:56 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/25 20:04:01 by aobshatk         ###   ########.fr       */
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

void	clear_command_proc(t_main_dat *main_data)
{
		restore_sys_files(main_data->stdin_cp, main_data->stdout_cp);
		unlink("heredoc");
		clear_sequence(&main_data->sequence);
		main_data->sequence = NULL;
}

int	built_in(char *arg)
{
	int	i;
	char **b_names;

	i = 0;
	b_names = ft_split("cd,echo,pwd,export,unset,env,exit", ',');
	while (b_names[i])
	{
		if (strncmp(b_names[i], arg, ft_strlen(arg)) == 0)
		{
			free_arr(b_names);
			return (i);
		}
		i++;
	}
	return (-1);
}

void	init_str(char **str, char **array)
{
	int	len;
	
	len = arr_len(array);
	if (len > 1)
		*str = ft_strjoin(array[0], " ");
	else
		*str = ft_strdup (array[0]);
}
