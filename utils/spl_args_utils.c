/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:39:52 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/30 23:28:42 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_args(char **res, t_args **args)
{
	if (*res)
	{
		add_node_a(args, create_node_a(ft_strdup(*res)));
		free(*res);
		*res = NULL;
	}
}

void	extract_outer_string(char **res, char *arg, int *i, t_args **args)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (*res && (arg[j] == '\"' || arg[j] == '\'' || arg[j] == ' '))
		{
			add_node_a(args, create_node_a(ft_strdup(*res)));
			free(*res);
			*res = NULL;
			return ;
		}
		add_to_str(res, 1, &arg[j]);
		j++;
		*i += 1;
	}
}

char	**create_argv(t_args **args)
{
	int		size;
	char	**argv;
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
		argv[size] = ft_strdup((temp->arg));
		temp = temp->next;
		size++;
	}
	argv[size] = NULL;
	return (argv);
}
