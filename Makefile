# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 11:51:53 by aobshatk          #+#    #+#              #
#    Updated: 2025/05/13 19:29:39 by aobshatk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFTPATH = libft/ft_printf/

IN_PROC = input_processor/input_processor.c 
UTILS = utils/helpers.c utils/processes.c utils/prompt.c utils/checkers.c

UTILOBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(UTILS)))
IN_PROC_OBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(IN_PROC)))
OBJS = $(IN_PROC_OBJS) $(UTILOBJS)

LIBFT = $(LIBFTPATH)/libftprintf.a
LIBR = minishell.a

NAME = minishell

HOSTNM := @$(shell hostname)

./objs/%.o: ./input_processor/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -DHSTNM=\"$(HOSTNM)\" -c $< -o $@

./objs/%.o: ./utils/%.c
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
