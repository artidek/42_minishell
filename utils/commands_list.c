/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:21:14 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/19 15:44:14 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_commands *new_command (char *path, char **agrv)
{
	t_commands	*new_command;

	new_command = malloc(sizeof(t_commands));
	if (!new_command)
		return (NULL);
	new_command->argv = **agrv;
	new_command->path = path;
	new_command->next = NULL;
	return (new_command);
}

void	add_command(t_commands **commands, t_commands *command)
{
	t_commands	*temp;

	temp = NULL;
	if (!*commands)
	{
		*commands = command;
		return;
	}
	temp = *commands;
	while(temp->next)
		temp = temp->next;
	temp->next = command;
}

void	del_command (t_commands *command)
{
	if (!command)
		return;
	free(command->path);
	free(command->argv);
	free(command);
}

void	clear_commands (t_commands **commands)
{
	t_commands *temp;

	while (*commands)
	{
		temp = (*commands)->next;
		del_command(*commands);
		*commands = temp;
	}
}
