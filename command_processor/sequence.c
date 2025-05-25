/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:04:04 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/23 21:09:30 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	iterate_next(char **redir_str, char *str, int *i)
{
	int	j;

	j = 0;
	if ((str[j] == '<' && str[j + 1] == ' ') || (str[j] == '>' && str[j + 1] == ' '))
	{
		add_to_str(redir_str, 1, &str[j]);
		j++;
		*i += 1;
		skip_space(&str[j], &j, i);
	}
	if ((str[j + 1] == '<' && str[j + 2] == ' ') || (str[j + 1] == '>' && str[j + 2] == ' '))
	{
		add_to_str(redir_str, 2, &str[j]);
		j += 2;
		*i += 2;
		skip_space(&str[j], &j, i);
	}
	while (str[j])
	{
		if ((str[j] == ' ' || str[j] == '>' || str[j] == '<') && j > 0)
			return ;
		add_to_str(redir_str, 1, &str[j]);
		*i += 1;
		j++;
	}
}

static void	update_cmd_str(char **cmd_str, char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '>' || str[j] == '<')
			return;
		add_to_str(cmd_str, 1, &str[j]);
		*i += 1;
		j++;
	}
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

static void	split_input(t_seq **sequence, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && ((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i
				+ 1] != '<')))
			update_redir_str(&((*sequence)->temp_redir), &i, 1, &str[i]);
		if (str[i] && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
				+ 1] == '<')))
			update_redir_str(&((*sequence)->temp_redir), &i, 2, &str[i]);
		if (str[i] && str[i] != '<' && str[i] != '>')
			update_cmd_str(&((*sequence)->temp_cmd), &str[i], &i);
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
