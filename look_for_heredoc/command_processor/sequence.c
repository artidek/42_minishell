/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:13:28 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/15 11:07:23 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_proc.h"

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
	return (new_seq);
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

void	add_sequence(t_seq **sequence)
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
