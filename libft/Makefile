# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/28 15:12:07 by ctaleb            #+#    #+#              #
#    Updated: 2021/03/19 16:44:41 by ctaleb           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar
ARFLAGS = rcs

INCS_PATH = .

SRCS = ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strlen.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_isgraph.c\
		ft_islower.c\
		ft_isupper.c\
		ft_ispunct.c\
		ft_isspace.c\
		ft_chrjoin.c\
		ft_chrrjoin.c\
		ft_numlen.c\
		ft_abs.c\
		ft_utoa.c\
		ft_utoa_base.c\
		ft_lutoa_base.c\
		ft_ishex.c\
		ft_ltoa.c\
		ft_lutoa.c\
		ft_get_next_line.c\
		ft_vec_rot.c

OBJS = $(SRCS:.c=.o)
INCS = libft.h
NAME = libft.a

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
MAGENTA = \033[35m
CYAN = \033[36m
ORANGE = \033[38:5:208m
WHITE = \033[38:5:15m
BRCYAN = \033[38:5:14m
DEFAULT = \033[0m

PROJECT = LIBFT
DELAY = 0.02

.PHONY = all $(NAME) bonus clean fclean re project all42 42logo

all: project $(NAME)

$(NAME): $(OBJS)
	@printf "$(DEFAULT)************** $(CYAN)making $(NAME)$(DEFAULT) **************\n"
	@printf "$(ORANGE)"
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@printf "                 $(GREEN)[lib done]$(DEFAULT)                     \n\n"

%.o: %.c $(INCS)
	@printf "$(YELLOW)building$(DEFAULT)	%-20s	" "$@"
	@$(CC) $(CFLAGS) -I$(INCS_PATH) -o $@ -c $<
	@printf "$(GREEN)[ok]$(DEFAULT)\n"

clean:
	@printf "$(RED)"
	$(RM) $(OBJS) $(OBNS)
	@printf "$(DEFAULT)"

fclean: clean
	@printf "$(RED)"
	$(RM) $(NAME)
	@printf "$(DEFAULT)"

re: fclean all

project:
	@printf "$(DEFAULT)********************************************\n"
	@printf "                    $(PROJECT)                   "
	@printf "$(DEFAULT)\n********************************************\n"

all42: fclean 42logo project all bonus

42logo:
	@printf "$(BRCYAN)"
	@clear
	@printf "$(BRCYAN):\n:\n \n \n \n \n$(WHITE)r\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)::\n+:\n  \n  \n  \n  \n$(WHITE)fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN):::\n:+:\n+  \n   \n   \n   \n$(WHITE).fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)::::\n :+:\n:+  \n    \n    \n    \n$(WHITE)n.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN):::::\n  :+:\n+:+  \n     \n     \n     \n$(WHITE)on.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)::::::\n   :+:\n +:+  \n+     \n      \n      \n$(WHITE)yon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN):::::::\n    :+:\n  +:+  \n#+     \n       \n       \n$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)::::::::\n:    :+:\n   +:+  \n+#+     \n        \n        \n#$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN) ::::::::\n+:    :+:\n    +:+  \n +#+     \n+        \n         \n##$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)  ::::::::\n:+:    :+:\n     +:+  \n  +#+     \n#+        \n          \n###$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)   ::::::::\n :+:    :+:\n      +:+  \n   +#+     \n+#+        \n#          \n####$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)    ::::::::\n  :+:    :+:\n       +:+  \n    +#+     \n +#+        \n+#          \n#####$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)     ::::::::\n   :+:    :+:\n        +:+  \n     +#+     \n  +#+        \n#+#          \n######$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)      ::::::::\n    :+:    :+:\n         +:+  \n      +#+     \n   +#+        \n #+#          \n#######$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN):      ::::::::\n     :+:    :+:\n+         +:+  \n       +#+     \n+   +#+        \n  #+#          \n########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)::      ::::::::\n      :+:    :+:\n:+         +:+  \n+       +#+     \n#+   +#+        \n   #+#          \n ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN):::      ::::::::\n:      :+:    :+:\n+:+         +:+  \n:+       +#+     \n+#+   +#+        \n    #+#          \n  ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN) :::      ::::::::\n+:      :+:    :+:\n +:+         +:+  \n+:+       +#+     \n#+#+   +#+        \n#    #+#          \n   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)  :::      ::::::::\n:+:      :+:    :+:\n+ +:+         +:+  \n +:+       +#+     \n+#+#+   +#+        \n+#    #+#          \n#   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)   :::      ::::::::\n :+:      :+:    :+:\n:+ +:+         +:+  \n  +:+       +#+     \n#+#+#+   +#+        \n#+#    #+#          \n##   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)    :::      ::::::::\n  :+:      :+:    :+:\n+:+ +:+         +:+  \n+  +:+       +#+     \n+#+#+#+   +#+        \n #+#    #+#          \n###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)     :::      ::::::::\n   :+:      :+:    :+:\n +:+ +:+         +:+  \n#+  +:+       +#+     \n#+#+#+#+   +#+        \n  #+#    #+#          \n ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)      :::      ::::::::\n    :+:      :+:    :+:\n  +:+ +:+         +:+  \n+#+  +:+       +#+     \n+#+#+#+#+   +#+        \n   #+#    #+#          \n  ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)       :::      ::::::::\n     :+:      :+:    :+:\n   +:+ +:+         +:+  \n +#+  +:+       +#+     \n#+#+#+#+#+   +#+        \n    #+#    #+#          \n   ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)        :::      ::::::::\n      :+:      :+:    :+:\n    +:+ +:+         +:+  \n  +#+  +:+       +#+     \n+#+#+#+#+#+   +#+        \n     #+#    #+#          \n    ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)         :::      ::::::::\n       :+:      :+:    :+:\n     +:+ +:+         +:+  \n   +#+  +:+       +#+     \n +#+#+#+#+#+   +#+        \n      #+#    #+#          \n     ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)          :::      ::::::::\n        :+:      :+:    :+:\n      +:+ +:+         +:+  \n    +#+  +:+       +#+     \n  +#+#+#+#+#+   +#+        \n       #+#    #+#          \n      ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)           :::      ::::::::\n         :+:      :+:    :+:\n       +:+ +:+         +:+  \n     +#+  +:+       +#+     \n   +#+#+#+#+#+   +#+        \n        #+#    #+#          \n       ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)            :::      ::::::::\n          :+:      :+:    :+:\n        +:+ +:+         +:+  \n      +#+  +:+       +#+     \n    +#+#+#+#+#+   +#+        \n         #+#    #+#          \n        ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)             :::      ::::::::\n           :+:      :+:    :+:\n         +:+ +:+         +:+  \n       +#+  +:+       +#+     \n     +#+#+#+#+#+   +#+        \n          #+#    #+#          \n         ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)              :::      ::::::::\n            :+:      :+:    :+:\n          +:+ +:+         +:+  \n        +#+  +:+       +#+     \n      +#+#+#+#+#+   +#+        \n           #+#    #+#          \n          ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)               :::      ::::::::\n             :+:      :+:    :+:\n           +:+ +:+         +:+  \n         +#+  +:+       +#+     \n       +#+#+#+#+#+   +#+        \n            #+#    #+#          \n           ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)                :::      ::::::::\n              :+:      :+:    :+:\n            +:+ +:+         +:+  \n          +#+  +:+       +#+     \n        +#+#+#+#+#+   +#+        \n             #+#    #+#          \n            ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)                 :::      ::::::::\n               :+:      :+:    :+:\n             +:+ +:+         +:+  \n           +#+  +:+       +#+     \n         +#+#+#+#+#+   +#+        \n              #+#    #+#          \n             ###   ########$(WHITE)lyon.fr\n"
	@sleep $(DELAY)
	@clear
	@printf "$(BRCYAN)                  :::      ::::::::\n                :+:      :+:    :+:\n              +:+ +:+         +:+  \n            +#+  +:+       +#+     \n          +#+#+#+#+#+   +#+        \n               #+#    #+#          \n              ###   ########$(WHITE)lyon.fr\n\n"
	@sleep $(DELAY)
