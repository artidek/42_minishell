/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:59:03 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:17:54 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_seq	*new_sequence(void)
{
	t_seq	*new_seq;

	new_seq = malloc(sizeof(t_seq));
	if (!new_seq)
		return (NULL);
	new_seq->temp_cmd = NULL;
	new_seq->temp_redir = NULL;
	new_seq->commands = malloc(sizeof(t_commands));
	new_seq->commands->argv = NULL;
	new_seq->commands->path = NULL;
	new_seq->redirect = NULL;
	new_seq->next = NULL;
	return (new_seq);
}

void	clear_sequence(t_seq **sequence)
{
	t_seq	*temp;

	temp = NULL;
	while (*sequence)
	{
		temp = (*sequence)->next;
		if ((*sequence)->temp_cmd)
			free((*sequence)->temp_cmd);
		if ((*sequence)->temp_redir)
			free((*sequence)->temp_redir);
		if ((*sequence)->commands->path)
			free((*sequence)->commands->path);
		if ((*sequence)->commands->argv)
			free_arr((*sequence)->commands->argv);
		if ((*sequence)->commands)
			free((*sequence)->commands);
		if ((*sequence)->redirect)
			clear_redirect(&((*sequence)->redirect));
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
		return ;
	}
	temp = *sequence;
	while (temp->next)
		temp = temp->next;
	temp->next = new_sequence();
}
