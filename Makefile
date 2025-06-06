# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 11:51:53 by aobshatk          #+#    #+#              #
#    Updated: 2025/06/06 14:57:34 by aobshatk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFTPATH = libft/ft_printf/

CMD_PROC = command_processor/command_processor.c command_processor/split_arguments.c command_processor/sequence.c command_processor/redirect.c \
		   command_processor/redir_launcher.c command_processor/heredoc.c command_processor/command_launcher.c command_processor/pipe_ms.c \
		   command_processor/heredoc_launcher.c command_processor/exit_handler.c
IN_PROC = input_processor/input_processor.c input_processor/prompt.c input_processor/env.c
UTILS = utils/helpers.c utils/processes.c utils/prompt.c utils/checkers.c utils/processes.c utils/prompt_utils.c \
		utils/spl_args_utils.c utils/arguments.c utils/valid.c utils/arguments.c utils/sequence_list.c utils/arguments.c utils/sequence_utils.c \
		utils/redir_list.c utils/paths.c utils/cmd_utils.c utils/tty_ctl.c utils/expand.c utils/parsing.c utils/clean_up.c utils/clean_up_utils.c \
		utils/clear_main_data.c
BUILTINS = builtins/cdpwd.c builtins/echo.c builtins/exit.c builtins/exp.c builtins/unset.c builtins/env.c builtins/echo_add.c
EXPAND = expand/expand_list.c expand/expand.c expand/parsing.c expand/utils.c expand/exp_helpers.c

UTILOBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(UTILS)))
IN_PROC_OBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(IN_PROC)))
CMD_PROC_OBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(CMD_PROC)))
BUILTINS_OBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(BUILTINS)))
EXPAND_OBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(EXPAND)))
OBJS = $(BUILTINS_OBJS) $(IN_PROC_OBJS) $(UTILOBJS) $(CMD_PROC_OBJS) $(EXPAND_OBJS)

LIBFT = $(LIBFTPATH)/libftprintf.a
LIBR = minishell.a

NAME = minishell

HOSTNM := @$(shell hostname)

./objs/%.o: ./builtins/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -DHSTNM=\"$(HOSTNM)\" -c $< -o $@

./objs/%.o: ./expand/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -DHSTNM=\"$(HOSTNM)\" -c $< -o $@

./objs/%.o: ./input_processor/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -DHSTNM=\"$(HOSTNM)\" -c $< -o $@

./objs/%.o: ./utils/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -DHSTNM=\"$(HOSTNM)\" -c $< -o $@

./objs/%.o: ./command_processor/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -DHSTNM=\"$(HOSTNM)\" -c $< -o $@

$(NAME): $(LIBR) $(LIBFT)
	@$(CC) $(CFLAGS) main.c objs/$(LIBR) $(LIBFT) -o $(NAME) -lncurses -ltinfo -lreadline -lc
	@echo "Build complete"

all: $(NAME)

$(LIBR): $(OBJS)
	@ar rcs objs/$(LIBR) $(OBJS)

$(LIBFT):
		@make -s -C $(LIBFTPATH) bonus

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFTPATH)
	@echo "Clean complete"

fclean: clean
	@make fclean -s -C $(LIBFTPATH)
	@rm -f ./objs/$(LIBR)
	@rm -f $(NAME)
	@rm -d objs
	@echo "Full clean complete"

re: fclean $(NAME)

.PHONY: all clean fclean re
