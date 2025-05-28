/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:42:18 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/28 23:31:00 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_expanded(char **arg, t_expand *exp)
{
	char	*temp;

	free(*arg);
	*arg = NULL;
	while (exp)
	{
		if (!*arg)
			*arg = ft_strdup(exp->exp_str);
		else
		{
			temp = ft_strdup(*arg);
			free(*arg);
			*arg = ft_strjoin(*arg, temp);
			free(temp);
		}
		exp = exp->next;
	}
}

void	skip_sp(char **str, char *arg, int *i)
{
	int	j;

	j = 0;
	while (arg[j] && arg[j] == ' ')
	{
		add_to_str(str, 1, arg + j);
		j++;
		*i += 1;
	}
}

void	update_expand(t_expand **exp, char **str, int ex)
{
	if (*str)
	{
		add_expand(exp, new_expand(*str, ex));
		free(*str);
		*str = NULL;
	}
}
