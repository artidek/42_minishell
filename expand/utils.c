/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:42:18 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/30 21:43:57 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	s_q_inner(char *arg, int *j, int *i, t_expand **exp)
{
	int	a;
	char	*str;

	a = 1;
	str = NULL;
	while (arg[a])
	{
		if (arg[a] != '$' && arg[a] != '\'' && arg[a] != ' ')
			add_to_str(&str, 1, arg + a);
		if (arg[a] == ' ' || arg[a] == '$' || arg[a] == '\'')
		{
			*j += 1;
			*i += 1;
			update_expand(exp, &str, 1);
			return;
		}
		a++;
		*j += 1;
		*i += 1;
	}
}

void	s_q_expand(char *arg, t_expand **exp, int *i)
{
	int	j;
	char	*str;

	j = 1;
	str = NULL;
	while (arg[j] && arg[j] != '\'')
	{
		if (arg[j] != '$')
		{
			add_to_str(&str, 1, &(*arg) + j);
			j++;
			*i += 1;
		}
		if (arg[j] && arg[j] == '$')
			s_q_inner(arg + j, &j, i, exp);
	}
	if (arg[j])
		*i += 1;
	update_expand(exp, &str, 0);
}

void	join_expanded(char **arg, t_expand *exp)
{
	free(*arg);

	*arg = NULL;
	while (exp)
	{
		add_to_str(arg, ft_strlen(exp->exp_str), exp->exp_str);
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
		add_expand(exp, new_expand(ft_strdup(*str), ex));
		free(*str);
		*str = NULL;
	}
}
