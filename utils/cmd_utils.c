/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:50:33 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:57:46 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*no_path_arg(t_seq **sequence, char **paths)
{
	char	*res;
	char	*arg;

	res = NULL;
	arg = (*sequence)->commands->argv[0];
	if (built_in(arg) < 0)
		res = find_path(arg, paths);
	return (res);
}

static int	init_path(t_seq **sequence, char **paths)
{
	int		i;
	char	*first_arg;

	i = 0;
	first_arg = (*sequence)->commands->argv[0];
	while ((*sequence)->commands->argv[i] && (*sequence)->commands->argv[0][i])
	{
		if ((*sequence)->commands->argv[0][i] == '/')
		{
			if (cmd_not_found(first_arg))
				return (0);
			else
			{
				(*sequence)->commands->path = ft_strdup(first_arg);
				return (1);
			}
		}
		i++;
	}
	(*sequence)->commands->path = no_path_arg(sequence, paths);
	if (!n_pth_bin(sequence))
		return (0);
	return (1);
}

static int	init_args(t_main_dat *main_dat, t_seq **sequence)
{
	int		i;
	char	**argv;

	i = 0;
	(*sequence)->commands->argv = split_arguments((*sequence)->temp_cmd);
	if (!check_valid((*sequence)->commands->argv))
		return (0);
	argv = (*sequence)->commands->argv;
	while (argv[i])
	{
		if (i == 0 && is_var((*sequence)->commands->argv, main_dat))
			return (0);
		expandable(&(*sequence)->commands->argv[i], main_dat);
		i++;
	}
	clean_up_arg(&(*sequence)->commands->argv);
	if (!(*sequence)->commands->argv[0])
		return (0);
	return (1);
}

static int	seq_size(t_seq *sequence)
{
	int	i;

	i = 0;
	while (sequence)
	{
		sequence = sequence->next;
		i++;
	}
	return (i);
}

int	fill_commands(t_main_dat *main_data, char **paths)
{
	t_seq	*temp;

	temp = main_data->sequence;
	if (seq_size(main_data->sequence) > 1)
		main_data->pipe = 1;
	while (temp)
	{
		if (!init_args(main_data, &temp))
			return (0);
		if (temp->commands->argv && !init_path(&temp, paths))
			return (0);
		temp = temp->next;
	}
	return (1);
}
