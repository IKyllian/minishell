# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/28 15:12:07 by ctaleb            #+#    #+#              #
#    Updated: 2021/11/02 08:27:55 by ctaleb           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fPIC

RM = rm -f

AR = ar
ARFLAGS = rcs

INCS_PATH = .

SRCS = ft_memset.c			\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memccpy.c		\
		ft_memmove.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strlen.c			\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_strtolower.c		\
		ft_strchr.c			\
		ft_strcmp.c			\
		ft_strrchr.c		\
		ft_strncmp.c		\
		ft_strlcpy.c		\
		ft_strlcat.c		\
		ft_strnstr.c		\
		ft_atoi.c			\
		ft_calloc.c			\
		ft_strdup.c			\
		ft_strndup.c		\
		ft_substr.c			\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_split.c			\
		ft_itoa.c			\
		ft_strmapi.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_isgraph.c		\
		ft_islower.c		\
		ft_isupper.c		\
		ft_ispunct.c		\
		ft_isspace.c		\
		ft_chrjoin.c		\
		ft_chrrjoin.c		\
		ft_numlen.c			\
		ft_abs.c			\
		ft_utoa.c			\
		ft_utoa_base.c		\
		ft_lutoa_base.c		\
		ft_ishex.c			\
		ft_ltoa.c			\
		ft_lutoa.c			\
		ft_get_next_line.c	\
		ft_vec_rot.c

OBJS = $(SRCS:.c=.o)
INCS = libft.h
NAME = libft.a

PROJECT = LIBFT

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -I$(INCS_PATH) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(OBNS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re