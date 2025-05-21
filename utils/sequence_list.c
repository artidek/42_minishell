/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:59:03 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/21 11:57:21 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void del (void *data)
{
	char *temp;
	temp = (char *)data;
	if (!temp)
		free(temp);
}

static t_seq	*new_sequence(void)
{
	t_seq	*new_seq;

	new_seq = malloc(sizeof(t_seq));
	if (!new_seq)
		return (NULL);
	new_seq->temp_cmd = NULL;
	new_seq->temp_redir = NULL;
	new_seq->commands.path = NULL;
	new_seq->commands.argv = NULL;
	new_seq->heredoc = NULL;
	new_seq->redir_append = NULL;
	new_seq->redir_in = NULL;
	new_seq->redir_out = NULL;
	new_seq->next = NULL;
	return (new_seq);
}

void	clear_sequence(t_seq **sequence)
{
	t_seq	*temp;

	temp = (*sequence);
	while (temp)
	{
		if ((*sequence)->heredoc)
			ft_lstclear(&((*sequence)->heredoc), del);
		if ((*sequence)->redir_out)
			ft_lstclear(&((*sequence)->redir_out), del);
		if ((*sequence)->redir_in)
			ft_lstclear(&((*sequence)->redir_in), del);
		if ((*sequence)->redir_append)
			ft_lstclear(&((*sequence)->redir_append), del);
		if ((*sequence)->commands.path)
			free((*sequence)->commands.path);
		if ((*sequence)->commands.argv)
			free_arr((*sequence)->commands.argv);
		free(*sequence);
		*sequence = temp;
	}
}

void	add_sequence(t_seq **sequence)
{
	t_seq *temp;

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
