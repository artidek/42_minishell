/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:11:25 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/29 18:41:32 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	double_quote(char **arg, t_expand **exp)
{
	(void)*arg;
	(void)*exp;
	return;
}

static void	n_q_inner(char *arg,  int *i, t_expand **exp)
{
	int	j;
	char	*str;

	j = 1;
	*i += 1;
	str = NULL;
	while (arg[j])
	{
		if (arg[j] != '$')
			add_to_str(&str, 1, arg + j);
		if (arg[j] && arg[j] == '$' && j > 0)
		{
			update_expand(exp, &str, 1);
			return;
		}
		j++;
		*i += 1;
	}
	update_expand(exp, &str, 1);
}

static void	no_quote(char **arg, t_expand **exp)
{
	int	i;
	char	*str;

	i = 0;
	str = NULL;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '$')
			n_q_inner(&(*arg)[i], &i, exp);
		if ((*arg)[i] && (*arg)[i] != '$')
		{
			add_to_str(&str, 1, &(*arg)[i]);
			i++;
		}
	}
	update_expand(exp, &str, 0);
}

static void	single_quote(char **arg, t_expand **exp)
{
	int	i;
	char	*str;
	
	i = 0;
	str = NULL;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'' && i > 0)
			s_q_expand(&(*arg)[i], exp, &i);
		add_to_str(&str, 1, (*arg) + i);
		i++;
	}
	update_expand(exp, &str, 0);
}

void	expandable(char **arg, t_main_dat *main_data)
{
	t_expand	*exp;

	exp = NULL;
	if (**arg == '\'')
		single_quote(arg, &exp);
	else if (**arg == '\"')
		double_quote(arg, &exp);
	else
		no_quote(arg, &exp);
	expand(&exp, main_data);
	join_expanded(arg, exp);
	clear_expand(&exp);
}
