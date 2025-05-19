/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/19 15:26:47 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	test_arguments(char **cmd_argv)
{
	int	i;

	i = 0;
	while(cmd_argv[i])
	{
		printf("%s\n", cmd_argv[i]);
		i++;
	}
}

static void	extract_seq_it(char **spl_in)
{
	char	**cmd_argv;

	cmd_argv = split_arguments(spl_in[0]);
	test_arguments(cmd_argv);
}

void	run_command_processor(t_main_dat *main_data)
{
	char	**spl_in;

	if (!*(main_data->input_data.input))
		return;
	main_data->sequence.pipe = 0;
	main_data->sequence.redir_paths.redir_in = NULL;
	main_data->sequence.redir_paths.redir_out = NULL;
	main_data->sequence.commands = NULL;
	spl_in = ft_split(main_data->input_data.input, '|');
	if (arr_len(spl_in) > 1)
		main_data->sequence.pipe = 1;
	if (!check_valid(spl_in))
	{
		free_arr(spl_in);
		return;
	}
	extract_seq_it(spl_in);
}
