/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:28:27 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 10:57:18 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_redir(t_seq **seq, int type, char **file)
{
	add_redirect(&((*seq)->redirect), new_redir(type, ft_strdup(*file)));
	free(*file);
}

static int	check_redir_type(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else if (str[0] == '>' && str[1] == '>')
		return (REDIR_APP);
	else if (str[0] == '<')
		return (REDIR_IN);
	else if (str[0] == '>')
		return (REDIR_OUT);
	return (0);
}

static void	skip_sign(char *str, int *i, char sign)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] != sign)
			return ;
		j++;
		*i += 1;
	}
}

static void	extract_redir(t_seq **seq, char *str)
{
	int		i;
	int		type;
	char	*file;

	i = 0;
	file = NULL;
	if (!(*seq)->redirect)
	{
		type = check_redir_type(&str[i]);
		skip_sign(&str[i], &i, str[i]);
	}
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			update_redir(seq, type, &file);
			type = check_redir_type(&str[i]);
			file = NULL;
			skip_sign(&str[i], &i, str[i]);
		}
		add_to_str(&file, 1, &str[i]);
		i++;
		if (!str[i])
			update_redir(seq, type, &file);
	}
}

int	fill_redir(t_main_dat *main_data)
{
	t_seq	*sequence;

	sequence = main_data->sequence;
	while (sequence)
	{
		if (sequence->temp_redir)
			extract_redir(&sequence, sequence->temp_redir);
		sequence = sequence->next;
	}
	sequence = main_data->sequence;
	while (sequence)
	{
		if (!launch_heredocs(sequence, main_data))
			return (0);
		sequence = sequence->next;
	}
	if (access("heredoc", R_OK) != -1)
		redir_in("heredoc");
	return (1);
}
