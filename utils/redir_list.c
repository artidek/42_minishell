/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:38:45 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/22 13:34:44 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

t_redir	*new_redir(int type, char *file)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return NULL;
	new_redir->file = file;
	new_redir->redir_type = type;
	new_redir->next = NULL;
	return (new_redir);
}

void	clear_redirect(t_redir **redirect)
{
	t_redir *temp;

	if (!*redirect)
		return ;
	while(*redirect)
	{
		temp = (*redirect)->next;
		if ((*redirect)->file)
			free((*redirect)->file);
		free(*redirect);
		*redirect = temp;
	}
}

void	add_redirect(t_redir	**redir, t_redir *new_redir)
{
	t_redir	*temp;

	if (!*redir && !new_redir)
		return ;
	if (!*redir)
	{
		*redir = new_redir;
		return;
	}
	temp = *redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}
