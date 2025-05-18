/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:30:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/15 11:06:10 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cmd_proc.h"

static char	*add_redir_path(char *path, int *i, char *delim_set)
{
	int	len;
	int	j;
	t_charset *charset;
	char	*res;

	charset = extract_string(path, delim_set);
	len = *(charset->count);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (charset)
	{
		res[j] = charset->chr;
		if (charset->chr >= 7 && charset->chr <= 13)
			len++;
		j++;
		charset = charset->next;
	}
	res[j] = 0;
	*i += len;
	clear_charset(&charset);
	return (res);
}

static void	skip_space(char *parse_str, int *i)
{
	while (parse_str[*i] == ' ')
		*i += 1;
}

static char	*add_to_sequence(char *parse_str, t_seq **sequence)
{
	int	i;

	i = 0;
	add_sequence(sequence);
	if (!sequence)
		return (NULL);
	while (parse_str[i] && parse_str[i] != ';')
	{
		if (parse_str[i] == '<' && i == 0)
		{
			i++;
			(*sequence)->redir_paths.redir_in = add_redir_path(&parse_str[i], &i, " ;");
		}
		if (parse_str[i] == '>')
		{
			i++;
			(*sequence)->redir_paths.redir_in = add_redir_path(&parse_str[i], &i, " ;");
		}
		if (parse_str[i] == ' ')
			skip_space(&parse_str[i],&i);
		//init_command(parse_str[i], &i);
	}
	if (parse_str[i])
		return (&parse_str[i]);
	return (NULL);
}

void	parse_input(char *input, t_seq **sequence)
{
	char	*parts;

	parts = input;
	parts = add_to_sequence(parts, sequence);
	while (parts)
		parts = add_to_sequence(parts, sequence);

}
