/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:58:26 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/13 21:23:10 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disable_echoctl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_echoctl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	cmd_not_found(char *arg, t_main_dat *main_data)
{
	if (!check_exist(arg))
	{
		handle_exit(main_data, 127);
		ft_printf("minishell: ");
		ft_printf("%s: No such file or directory\n", arg);
		return (1);
	}
	return (0);
}

int	is_dir(t_main_dat *main_data)
{
	t_seq *temp;
	DIR	*op_dir;

	temp = main_data->sequence;
	while (temp)
	{
		if (built_in(temp->commands->argv[0]) >= 0)
			return (0);
		op_dir = opendir(temp->commands->path);
		if (op_dir)
		{
			ft_printf("minishell: %s is a directory\n", temp->commands->path);
			closedir(op_dir);
			return (1);
		}
		else
		{
			closedir(op_dir);
			return (0);
		}
		temp = temp->next;
	}

	return (0);
}

void	last_command(t_main_dat *main_data, t_seq *sequence)
{
	t_shenv	*temp;

	temp = main_data->env_cp;
	while(temp)
	{
		if (ft_strncmp("_", temp->key, ft_strlen(temp->key)) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(sequence->commands->argv[0]);
		}
		temp = temp->next;
	}
}
