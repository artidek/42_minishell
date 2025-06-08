/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:48:33 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/08 18:58:54 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_quote(char *str, int *i, char quote)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == quote)
		{
			*i += 1;
			return;
		}
		j++;
		*i += 1;
	}
}

static void	iterate_next(char **redir_str, char *str, int *i)
{
	int	j;

	j = 0;
	if ((str[j] == '<' && str[j + 1] == ' ') || (str[j] == '>' && str[j
			+ 1] == ' '))
	{
		add_to_str(redir_str, 1, &str[j]);
		j++;
		*i += 1;
		skip_space(&str[j], &j, i);
	}
	if ((str[j + 1] == '<' && str[j + 2] == ' ') || (str[j + 1] == '>' && str[j
			+ 2] == ' '))
	{
		add_to_str(redir_str, 2, &str[j]);
		j += 2;
		*i += 2;
		skip_space(&str[j], &j, i);
	}
	proceed_iterate(redir_str, str, i, j);
}


static void	update_redir_str(char **redir_str, int *i, int num_symb, char *str)
{
	int	j;

	j = 0;
	if (num_symb > 1 && !*redir_str)
	{
		add_to_str(redir_str, 2, str);
		*i += 2;
		j = 2;
		if (str[j] == ' ')
			skip_space(&str[j], &j, i);
	}
	else if (num_symb == 1 && !*redir_str)
	{
		add_to_str(redir_str, 1, str);
		*i += 1;
		j = 1;
		if (str[j] == ' ')
			skip_space(&str[j], &j, i);
	}
	iterate_next(redir_str, &str[j], i);
}

void	redir_str(t_seq **sequence, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quote(&str[i + 1], &i, str[i]);
		if (str[i] && ((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<'
					&& str[i + 1] != '<')))
			update_redir_str(&((*sequence)->temp_redir), &i, 1, &str[i]);
		if (str[i] && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<'
					&& str[i + 1] == '<')))
			update_redir_str(&((*sequence)->temp_redir), &i, 2, &str[i]);
		if (str[i])
			i++;
	}
}
