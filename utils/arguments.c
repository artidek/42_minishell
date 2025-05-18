/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:09:57 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/18 19:32:47 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_a(char *argument)
{
	if (argument)
		free(argument);
}

t_args	*create_node_a(char *argument)
{
	t_args	*new_node;

	new_node = malloc(sizeof(t_args));
	if (!new_node)
		return (NULL);
	new_node->arg = argument;
	new_node->next = NULL;
	return (new_node);
}

void	add_node_a(t_args **lst, t_args *new)
{
	t_args	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	clear_list_a(t_args **lst, void (*del_a)(char *))
{
	t_args	*temp;

	if (!lst || !del_a)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		delete_node_a(*lst, del_a);
		*lst = temp;
	}
}

void	delete_node_a(t_args *lst, void (*del_a)(char *))
{
	if (!lst || !del_a)
		return ;
	del_a(lst->arg);
	free(lst);
}
