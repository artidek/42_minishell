/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:16:12 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	launch_sequence(t_main_dat *main_data)
{
	if (!main_data->pipe)
		single_command(main_data);
	else
		start_piping(main_data);
	restore_sys_files(main_data->stdin_cp, main_data->stdout_cp);
	unlink("heredoc");
	clear_sequence(&main_data->sequence);
	main_data->sequence = NULL;
}

static void	argv_cmd(t_seq **sequence)
{
	t_seq	*seq;
	char	**tmp;

	seq = *sequence;
	while (seq)
	{
		if (strrchr(seq->commands->argv[0], '/'))
		{
			tmp = ft_split(seq->commands->argv[0], '/');
			free(seq->commands->argv[0]);
			seq->commands->argv[0] = ft_strdup(tmp[arr_len(tmp) - 1]);
			free_arr(tmp);
		}
		seq = seq->next;
	}
}

static char	**get_paths(t_shenv *env)
{
	char	**paths;

	paths = NULL;
	while (env)
	{
		if (strncmp("PATH", env->key, ft_strlen(env->key)) == 0)
		{
			paths = ft_split(env->value, ':');
			return (paths);
		}
		env = env->next;
	}
	if (!paths)
	{
		paths = malloc(sizeof(char *) * 2);
		paths[0] = ft_strdup("/");
		paths[1] = NULL;
	}
	return (paths);
}

static int	init_commands(t_main_dat *main_data)
{
	char	**paths;

	paths = get_paths(main_data->env_cp);
	if (!main_data->sequence->temp_cmd)
		return (1);
	if (!fill_commands(main_data, paths))
	{
		free_arr(paths);
		restore_sys_files(main_data->stdin_cp, main_data->stdout_cp);
		unlink("heredoc");
		clear_sequence(&main_data->sequence);
		main_data->sequence = NULL;
		return (0);
	}
	free_arr(paths);
	return (1);
}

void	run_command_processor(t_main_dat *main_data)
{
	char	**spl_in;

	main_data->stdin_cp = dup(STDIN_FILENO);
	main_data->stdout_cp = dup(STDOUT_FILENO);
	if (!*(main_data->input_data.input))
		return ;
	spl_in = ft_split(main_data->input_data.input, '|');
	init_sequence(main_data, spl_in);
	free_arr(spl_in);
	if (!fill_redir(main_data))
		return ;
	if (!init_commands(main_data))
		return ;
	if (main_data->sequence->commands->argv)
		argv_cmd(&(main_data->sequence));
	launch_sequence(main_data);
	main_data->pipe = 0;
	restore_sys_files(main_data->stdin_cp, main_data->stdout_cp);
	unlink("heredoc");
	clear_sequence(&(main_data->sequence));
	main_data->sequence = NULL;
}
