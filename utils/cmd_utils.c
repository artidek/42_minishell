/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:50:33 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/25 20:06:47 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_path(t_seq **sequence, char **paths)
{
	int	i;

	i = 0;
	while ((*sequence)->commands->argv[0][i])
	{
		if ((*sequence)->commands->argv[0][i] == '/')
		{
			if (!check_exist((*sequence)->commands->argv[0]))
				return (0);
			else
			{
				(*sequence)->commands->path = ft_strdup((*sequence)->commands->argv[0]);
				return (1);
			}
		}
		i++;
	}
	if (built_in((*sequence)->commands->argv[0]) < 0)
		(*sequence)->commands->path = find_path((*sequence)->commands->argv[0], paths);
	if (!(*sequence)->commands->path && built_in((*sequence)->commands->argv[0]) < 0)
		return (0);
	return (1);
}

static int	init_args(t_main_dat *main_dat, t_seq **sequence)
{
	int	i;
	char	**argv;

	i = 0;
	(*sequence)->commands->argv = split_arguments((*sequence)->temp_cmd);
	argv = (*sequence)->commands->argv;
	if (!check_valid((*sequence)->commands->argv))
		return (0);
	while (argv[i])
	{
		if (argv[i][0] == '$' || argv[i][0] == '\"')
			expandable(&(*sequence)->commands->argv[i], main_dat);
		trim_arg(&(*sequence)->commands->argv[i]);
		i++;
	}
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
		if (!init_path(&temp, paths))
		{
			perror("minishell");
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
