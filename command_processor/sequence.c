/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:04:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/08 19:05:52 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	iterate_cmd(char *str, int *i, int *j)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] == '<' || str[a] == '>')
			a++;
		if (str[a] == '<' || str[a] == '>')
			a++;
		if (str[a] == ' ')
		{
			while (str[a] && str[a] == ' ')
				a++;
		}
		a++;
		if (!str[a] || str[a] == ' ' || str[a] == '\'' || str[a] == '\"')
		{
			*j += a;
			*i += a;
			return;
		}
	}
}

static void	update_cmd_str(char **cmd_str, char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '>' || str[j] == '<')
		{
			iterate_cmd(&str[j], i , &j);
			return;
		}
		if (str[j] == '\'' || str[j] == '\"')
			return;
		if (str[j])
		{
			add_to_str(cmd_str, 1, &str[j]);
			*i += 1;
			j++;
		}
	}
}

static void	in_quotes(t_seq **sequence, char *str, int *i, char quote)
{
	int	j;

	j = 1;
	add_to_str(&(*sequence)->temp_cmd, 1, str);
	*i += 1;
	while (str[j])
	{
		add_to_str(&(*sequence)->temp_cmd, 1, &str[j]);
		if (str[j] == quote)
		{
			*i += 1;
			return ;
		}
		j++;
		*i += 1;
	}
}

static void	split_input(t_seq **sequence, char *str)
{
	int	i;

	i = 0;
	redir_str(sequence, str);
	while (str[i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
			in_quotes(sequence, &str[i], &i, str[i]);
		if (str[i])
			update_cmd_str(&((*sequence)->temp_cmd), &str[i], &i);
		if (str[i] && str[i] != '\"' && str[i] != '\'')
			i++;
	}
}

void	init_sequence(t_main_dat *main_data, char **in_arr)
{
	int		i;
	t_seq	*sequence;
	t_seq	*temp;

	sequence = NULL;
	i = 0;
	while (in_arr && in_arr[i])
	{
		add_sequence(&sequence);
		i++;
	}
	i = 0;
	temp = sequence;
	while (temp)
	{
		split_input(&temp, in_arr[i]);
		temp = temp->next;
		i++;
	}
	main_data->sequence = sequence;
}
