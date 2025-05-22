/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/22 13:48:16 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void test_redir(t_main_dat *main_data)
{
	t_seq	*seq = main_data->sequence;
	t_redir	*redir;
	while (seq)
	{
		redir = seq->redirect;
		while (redir)
		{
			printf("redir type %d, redir file %s\n", redir->redir_type, redir->file);
			redir = redir->next;
		}
		seq = seq->next;
	}
}

static void	extract_seq_it(char **spl_in, t_main_dat *main_data)
{
	init_sequence(main_data, spl_in);
}

void	run_command_processor(t_main_dat *main_data)
{
	char	**spl_in;

	if (!*(main_data->input_data.input))
		return;
	spl_in = ft_split(main_data->input_data.input, '|');
	extract_seq_it(spl_in, main_data);
	fill_redir(main_data);
	test_redir(main_data);
	free_arr(spl_in);
	clear_sequence(&(main_data->sequence));
	main_data->sequence = NULL;
}
