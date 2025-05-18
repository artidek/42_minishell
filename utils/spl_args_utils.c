/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:39:52 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/18 19:29:00 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ext_qt(char **arg, char **res, int *i)
{
	(*res)[*i] = *(*arg);
	(*i)++;
	(*arg)++;
	(*res)[*i] = *(*arg);
	(*i)++;
	(*arg)++;
}

void	update_list(t_args **args, char *arg)
{
	if (!args)
		*args = create_node_a(arg);
	else
		add_node_a(args, create_node_a(arg));
}

char	**create_argv(t_args **args)
{
	int			size;
	char		**argv;
	t_args	*temp;

	size = 0;
	temp = *args;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	temp = *args;
	argv = (char **)malloc(sizeof(char *) * (size + 2));
	size = 0;
	while (temp)
	{
		argv[size] = ft_strdup(temp->arg);
		temp = temp->next;
		size++;
	}
	argv[size] = NULL;
	return (argv);
}
