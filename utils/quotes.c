/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:58:47 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/29 20:20:44 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static void	handle_sig(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}

static void	get_quotes(char quote, int write_end)
{
	char	*input;

	seg_init(SIGINT, handle_sig);
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			ft_printf("minishell: unexpected EOF while looking for matching `\"\'\n");
			ft_printf("minishell: syntax error: unexpected end of file\n");
			close(write_end);
			exit(1);
		}
		if (*input && stop_quotes(quote, input))
		{
			write_quotes(write_end, input);
			close(write_end);
			exit(0);
		}
		if (*input)
			write_quotes(write_end, input);
	}
}

static void	read_pipe(char **arg, int read_end)
{
	char buf[2];
	int	r_len;

	ft_memset(buf, 0, 2);
	r_len = read(read_end, buf, 1);
	if (*buf)
		add_to_str(arg, 1, &buf[0]);
	while (r_len > 0)
	{
		r_len = read(read_end, buf, 1);
		if (*buf)
			add_to_str(arg, 1, &buf[0]);
	}
	close(read_end);
}

static char	find_quote(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (arg[0] == '\"' || arg[len - 1] == '\"')
		return ('\"');
	if (arg[0] == '\'' || arg[len - 1] == '\'')
		return ('\'');
	return (0);
}

int	close_quotes(char **arg)
{
	int	pid;
	int	status;
	int	pipefd[2];
	char	quote;
	struct sigaction	sa_orig;

	sig_ignore(&sa_orig);
	quote = find_quote(*arg);
	if (!create_pipe(pipefd))
		return (0);
	pid = fork();
	if(process_failed(pid))
		return (0);
	if (pid == 0)
	{
		close(pipefd[0]);
		get_quotes(quote, pipefd[1]);
	}
	close(pipefd[1]);
	read_pipe(arg, pipefd[0]);
	waitpid(pid, &status, 0);
	sig_restore(&sa_orig);
	if (WEXITSTATUS(status) == 1)
		return (0);
	return (1);
}
