/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/23 16:29:52 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	extract_seq_it(char **spl_in, t_main_dat *main_data)
{
	init_sequence(main_data, spl_in);
}

void	run_command_processor(t_main_dat *main_data)
{
	char	**spl_in;
	int	stdin_cp;
	int	stdout_cp;

	stdin_cp = dup(STDIN_FILENO);
	stdout_cp = dup(STDOUT_FILENO);
	if (!*(main_data->input_data.input))
		return;
	spl_in = ft_split(main_data->input_data.input, '|');
	extract_seq_it(spl_in, main_data);
	fill_redir(main_data);
	free_arr(spl_in);
	if (!launch_redir(main_data->sequence))
	{
		restore_sys_files(stdin_cp, stdout_cp);
		clear_sequence(&(main_data->sequence));
		main_data->sequence = NULL;
		unlink("heredoc");
		return;
	}
	restore_sys_files(stdin_cp, stdout_cp);
	unlink("heredoc");
	clear_sequence(&(main_data->sequence));
	main_data->sequence = NULL;
}
