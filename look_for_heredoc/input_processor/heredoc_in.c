/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:45:49 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/17 19:58:18 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_history(char *input, t_main_dat *main_data)
{
	char	*hist;
	char	*temp;

	temp = ft_strjoin(main_data->input_data.heredoc_in.line, "\n");
	hist = ft_strjoin(temp, input);
	add_history(hist);
	free(temp);
	free(hist);
}

static void	update_line(char **input, t_main_dat *main_data)
{
	char	*temp;

	temp = ft_strdup(main_data->input_data.heredoc_in.line);
	free(main_data->input_data.heredoc_in.line);
	main_data->input_data.heredoc_in.line = ft_strjoin(temp, "\n");
	free(temp);
	temp = ft_strdup(main_data->input_data.heredoc_in.line);
	free(main_data->input_data.heredoc_in.line);
	main_data->input_data.heredoc_in.line = ft_strjoin(temp, *input);
	free(temp);
	free(*input);
	*input = NULL;
}

static char	**get_heredoc(char *eof, t_main_dat *main_data)
{
	char	*input;

	if (main_data->input_data.prompt)
		free(main_data->input_data.prompt);
	main_data->input_data.prompt = ft_strdup(">");
	while (1)
	{
		input = read_input(main_data);
		if (!input || *(main_data->input_data.heredoc_in.stop_heredoc) == 1)
			return (NULL);
		if (input && *input && eof && !ft_strncmp(input, eof, ft_strlen(eof)))
		{
			free(main_data->input_data.prompt);
			main_data->input_data.prompt = NULL;
			update_history(input, main_data);
			if (input)
				free(input);
			input = NULL;
			return (ft_split(main_data->input_data.heredoc_in.line, '\n'));
		}
		if (input && *input)
			update_line(&input, main_data);
		if (input && !(*input))
			free(input);
	}
}

void	heredoc_in(char *input, t_main_dat *main_data)
{
	char	*eof;
	char	*start;
	char	*temp;

	eof = NULL;

	temp = ft_strdup(input);
	start = ft_strchr(temp, '<');
	if (*(start + 2))
		eof = ft_strtrim(start + 2, "; |>");
	free(temp);
	main_data->input_data.heredoc_in.line = ft_strdup(input);
	if (eof)
		main_data->input_data.heredoc_in.heredoc_data = get_heredoc(eof, main_data);
	if (!main_data->input_data.heredoc_in.heredoc_data)
	{
		free(eof);
		eof = NULL;
		free(main_data->input_data.heredoc_in.line);
		main_data->input_data.heredoc_in.line = NULL;
	}
	*(main_data->input_data.heredoc_in.stop_heredoc) = 0;
	if (eof)
		free(eof);
}

int	is_heredoc(char *input)
{
	char	*start;

	start = NULL;
	if (!*input)
		return (0);
	start = ft_strchr(input, '<');
	if (start)
	{
		start++;
		if (*start && *start == '<')
			return (1);
	}
	return (0);
}
