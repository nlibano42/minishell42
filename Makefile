# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 03:58:55 by nlibano-          #+#    #+#              #
#    Updated: 2023/03/14 19:55:01 by jdasilva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Folders and Names
NAME		= minishell
SRCSDIR		= srcs
OBJSDIR		= objs
EXTLIB		= libft
#READLINE_DIR = /usr/local/Cellar/readline/8.2.1
READLINE_DIR = ${HOME}/.brew/opt/readline

SRCS	= main.c\
		../gnl/get_next_line_utils.c \
		../gnl/get_next_line.c \
		env.c\
		lst_env.c\
		signal.c\
		free_params.c\
		linecontrol.c\
		utils.c\
		pipecontrol.c\
		deletequotes.c\
		init.c\
		check.c\
		check2.c\
		split.c\
		redirections.c\
		error.c\
		path.c\
		lst_pipe.c\
		built.c\
		lst_redir.c\
		pipe.c\
		export.c\
		pwd.c\
		exit.c\
		echo.c\
		unset.c\
		cd.c\
		expand_utils.c\
		here_doc.c\
		
# Compiler options
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
F_READLINE	= -I$(READLINE_DIR)/include
DFLAG		= -lreadline -L$(READLINE_DIR)/lib

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################

OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)

all:$(NAME)

$(NAME): $(OBJS) $(EXTLIB)/$(EXTLIB).a
	@echo "Assembling $@"
	@$(CC) $(CFLAGS) -o $@  $(DFLAG)   $^

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	$(CC) $(CFLAGS) $(F_READLINE) -I$(EXTLIB) -c $< -o $@

$(EXTLIB)/$(EXTLIB).a:
	@echo "Compiling $@"
	@$(MAKE) -s -C $(EXTLIB) > /dev/null

clean:
	rm -rf $(OBJSDIR)
	@$(MAKE) -s -C $(EXTLIB) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -s -C $(EXTLIB) fclean

re: fclean all

.PHONY: all clean fclean re

