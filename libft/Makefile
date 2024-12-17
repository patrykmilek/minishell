# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpyciarz <jpyciarz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 12:34:04 by jpyciarz          #+#    #+#              #
#    Updated: 2024/03/12 12:34:08 by jpyciarz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_bzero\
ft_isalnum\
ft_isalpha\
ft_isascii\
ft_isdigit\
ft_isprint\
ft_memcpy\
ft_memset\
ft_strlcpy\
ft_strlen\
ft_strlcat\
ft_toupper\
ft_tolower\
ft_strchr\
ft_strrchr\
ft_strncmp\
ft_memchr\
ft_memcmp\
ft_strnstr\
ft_atoi\
ft_calloc\
ft_strdup\
ft_substr\
ft_strjoin\
ft_strtrim\
ft_split\
ft_itoa\
ft_strmapi\
ft_striteri\
ft_putchar_fd\
ft_putstr_fd\
ft_putendl_fd\
ft_putnbr_fd\
ft_memmove\
get_next_line\
ft_strcmp

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))


.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re