/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/15 10:47:54 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_proc.h"

static void		test_sequence (t_seq *seq)
{
	while (seq)
	{
		if (seq->redir_paths.redir_in)
			printf("redirect in %s\n",  seq->redir_paths.redir_in);
		if (seq->redir_paths.redir_out)
			printf("redirect out %s\n",  seq->redir_paths.redir_out);
		seq = seq->next;
	}
}
void	run_command_processor(char *input)
{
	t_seq	*sequence;

	sequence = NULL;
	parse_input(input, &sequence);
	if (!sequence)
	{
		ft_printf("minishell: unable to execute command\n");
		return;
	}
	test_sequence(sequence);
	clear_sequence(&sequence);
}
