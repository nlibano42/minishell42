# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlibano- <nlibano-@student.42urduli>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 20:13:39 by nlibano-          #+#    #+#              #
#    Updated: 2021/11/09 11:50:26 by nlibano-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBC = ar rcs

RM = /bin/rm -f

SRC = ft_strlen.c \
	  ft_split.c \
	  ft_memcpy.c \
	  ft_strlcpy.c \
	  ft_strdup.c

	#   ft_isdigit.c \
	#   ft_isalnum.c \
	#   ft_isascii.c \
	#   ft_isprint.c \
	#   ft_strlen.c \
	#   ft_memset.c \
	#   ft_bzero.c \
	#   ft_memmove.c \
	#   ft_strlcat.c \
	#   ft_toupper.c \
	#   ft_tolower.c \
	#   ft_strchr.c \
	#   ft_strrchr.c \
	#   ft_strncmp.c \
	#   ft_memchr.c \
	#   ft_memcmp.c \
	#   ft_strnstr.c \
	#   ft_atoi.c \
	#   ft_calloc.c \
	#   ft_substr.c \
	#   ft_strjoin.c \
	#   ft_strtrim.c \
	#   ft_itoa.c \
	#   ft_strmapi.c \
	#   ft_striteri.c \
	#   ft_putchar_fd.c \
	#   ft_putstr_fd.c \
	#   ft_putendl_fd.c \
	#   ft_putnbr_fd.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(LIBC) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
