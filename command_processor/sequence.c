/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:13:28 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/14 18:30:28 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_proc.h"

static void	init_redir(t_seq **sequence)
{
	(*sequence)->redir_paths.redir_in = NULL;
	(*sequence)->redir_paths.redir_out = NULL;
}

static t_seq	*new_sequence(void)
{
	t_seq	*new_seq;
	
	new_seq = malloc(sizeof(t_seq));
	if (!new_seq)
		return (NULL);
	new_seq->commands = NULL;
	new_seq->redir_in_fd = -1;
	new_seq->redir_out_fd = -1;
	new_seq->redir_paths.redir_in = NULL;
	new_seq->redir_paths.redir_out = NULL;
	new_seq->next = NULL;
}

void	clear_sequence(t_seq **sequence)
{
	t_seq	*temp;

	temp = (*sequence);
	while (temp)
	{
		temp = (*sequence)->next;
		if ((*sequence)->redir_paths.redir_in)
			free((*sequence)->redir_paths.redir_in);
		if ((*sequence)->redir_paths.redir_out)
			free((*sequence)->redir_paths.redir_out);
		if ((*sequence)->commands)
			printf("command cleared\n");
			//clear_commands(&((*sequence)->commands));
		free(*sequence);
		*sequence = temp;
	}
}

void	add_sequnce(t_seq **sequence)
{
	t_seq	*temp;

	if (!(*sequence))
	{
		*sequence = new_sequence();
		return;
	}
	temp = *sequence;
	while (temp->next)
		temp = temp->next;
	temp->next = new_sequence();
}
