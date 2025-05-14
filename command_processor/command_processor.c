/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/14 18:19:09 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_proc.h"

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
